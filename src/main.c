#include "../philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
		}
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	add_to_list(t_philo *philo, t_data *data, int n)
{
	t_philo	*new_philo;
	t_philo	*first;

	first = philo;
	new_philo = (t_philo *) malloc (sizeof(t_philo));
	pthread_mutex_init(&new_philo->fork, NULL);
	new_philo->id = n + 1;
	new_philo->data = data;
	while (philo->next != first)
		philo = philo->next;
	philo->next = new_philo;
	new_philo->next = first;
	new_philo->prev = philo;
	first->prev = new_philo;
}

void	init_philo_list(t_data *data)
{
	int	n;

	data->philo = (t_philo *) malloc (sizeof(t_philo));
	pthread_mutex_init(&data->philo->fork, NULL);
	data->philo->data = data;
	data->philo->id = 1;
	data->philo->next = data->philo;
	data->philo->prev = data->philo;
	n = 0;
	while (++n < data->philo_num)
		add_to_list(data->philo, data, n);
}

void	*philo_func(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->fork);
	printf ("%i grabbed right fork\n", philo->id);
	pthread_mutex_lock(&philo->prev->fork);
	printf ("%i grabbed left fork\n", philo->id);
	usleep(philo->data->eat_time);
	pthread_mutex_unlock(&philo->prev->fork);
	printf ("%i dropped left fork\n", philo->id);
	pthread_mutex_unlock(&philo->fork);
	printf ("%i dropped right fork\n", philo->id);
	return (NULL);
}

void	start_threads(t_data *data)
{
	int	n;
	t_philo	*temp;

	n = data->philo_num;
	temp = data->philo;
	while (n > 0)
	{
		pthread_create(&temp->thread, NULL, (void *)&philo_func, temp);
		temp = temp->next;
		n--;
	}
	n = data->philo_num;
	while (n > 0)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
		n--;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		printf ("Incorrect number of arguments\n");
		exit (1);
	}
	else if (check_args(argv) == 0)
	{
		printf("Arguments are formatted incorrectly\n");
		exit (1);
	}
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]) * 1000;
	data->eat_time = ft_atoi(argv[3]) * 1000;
	data->sleep_time = ft_atoi(argv[4]) * 1000;
	if (argv[5] != NULL)
		data->eat_num = ft_atoi(argv[5]);
	data->start_time = get_time();
	init_philo_list(data);
	start_threads(data);
}

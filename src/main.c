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
	new_philo->eat_count = 0;
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
	data->philo->eat_count = 0;
	data->philo->next = data->philo;
	data->philo->prev = data->philo;
	n = 0;
	while (++n < data->philo_num)
		add_to_list(data->philo, data, n);
}

void	*philo_func(t_philo *philo)
{
	philo->last_eat_time = get_time();
	if (philo->id % 2 == 0)
		usleep((philo->data->eat_time - 10) * 1000);
	while (philo->data->dead == 0 && (philo->eat_count < philo->data->eat_num \
			|| philo->data->eat_num == -1))
	{
		philo_fork_lock(philo);
		philo_eat(philo);
		philo_fork_unlock(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	eat_count_check(t_data *data)
{
	t_philo *philo;

	philo = data->philo;
	if (philo->eat_count != data->eat_num)
		return (0);
	philo = philo->next;
	while (philo != data->philo)
	{
		if (philo->eat_count != data->eat_num)
			return (0);
		philo = philo->next;
	}
	data->dead = 1;
	return (1);
}

void	death_check(t_data *data)
{
	t_philo	*philo;

	usleep (data->die_time - 10);
	philo = data->philo;
	while (data->dead == 0)
	{
		if (eat_count_check(data))
			break ;
		if (get_time() - philo->last_eat_time > data->die_time)
		{
			printf ("%lli %i died\n", get_time() - data->start_time, philo->id);
			data->dead = 1;
		}
		philo = philo->next;
	}
}

void	start_threads(t_data *data)
{
	int	n;
	t_philo	*temp;

	n = data->philo_num;
	temp = data->philo;
	pthread_mutex_init(&data->printer, NULL);
	data->start_time = get_time();
	while (n > 0)
	{
		pthread_create(&temp->thread, NULL, (void *)&philo_func, temp);
		temp = temp->next;
		n--;
	}
	death_check(data);
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
	data = (t_data *) malloc (sizeof(t_data));
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->dead = 0;
	if (argv[5] != NULL)
		data->eat_num = ft_atoi(argv[5]);
	else
		data->eat_num = -1;
	init_philo_list(data);
	start_threads(data);
	free_all(data);
}

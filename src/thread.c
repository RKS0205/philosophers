#include "../philo.h"

static void	*philo_func(t_philo *philo)
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

void	start_threads(t_data *data)
{
	int	n;
	t_philo	*temp;

	n = data->philo_num;
	temp = data->philo;
	pthread_mutex_init(&data->printer, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
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
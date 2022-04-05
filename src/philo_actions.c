#include "../philo.h"

void	philo_fork_lock(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i has taken a fork\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_lock(&philo->prev->fork);
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i has taken a fork\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
	}
}

void	philo_fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		philo->last_eat_time = get_time();
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is eating\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
		philo->eat_count++;
		usleep(philo->data->eat_time * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is sleeping\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
		usleep(philo->data->sleep_time * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is thinking\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
	}
}
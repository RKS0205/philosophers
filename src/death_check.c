#include "../philo.h"

static int	eat_count_check(t_data *data)
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

	usleep ((data->die_time * 1000) - 10);
	philo = data->philo;
	while (data->dead == 0)
	{
		if (eat_count_check(data))
			break ;
		pthread_mutex_lock(&data->death_mutex);
		if (get_time() - philo->last_eat_time > data->die_time)
		{
			printf ("%lli %i died\n", get_time() - data->start_time, philo->id);
			data->dead = 1;
		}
		pthread_mutex_unlock(&data->death_mutex);
		philo = philo->next;
	}
}

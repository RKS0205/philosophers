#include "../philo.h"

void	free_all(t_data *data)
{
	if (data->philo_num == 1)
	{
		free(data->philo);
		free (data);
	}
	else
	{
		while (data->philo_num > 1)
		{
			data->philo = data->philo->next;
			free (data->philo->prev);
			data->philo_num--;
		}
		free(data->philo);
		free(data);
	}
}
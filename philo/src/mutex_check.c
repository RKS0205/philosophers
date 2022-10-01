/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 01:17:27 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/05/02 01:17:28 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (1);
}

int	check_eat_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->eat_count != philo->data->eat_num)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	return (0);
}

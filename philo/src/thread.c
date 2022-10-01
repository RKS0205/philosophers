/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:28:15 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/04/06 02:28:15 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*philo_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_time_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->eat_time_mutex);
	if (philo->id % 2 == 0)
		usleep((philo->data->eat_time - 10) * 1000);
	while (check_stop(philo->data) && (philo->eat_count < philo->data->eat_num \
			|| philo->data->eat_num == -1))
	{
		philo_fork_lock(philo);
		if (check_stop(philo->data) == 0)
			break ;
		philo_eat(philo);
		philo_fork_unlock(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	start_threads(t_data *data)
{
	int		n;
	t_philo	*temp;

	n = data->philo_num;
	temp = data->philo;
	pthread_mutex_init(&data->printer, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->eat_time_mutex, NULL);
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

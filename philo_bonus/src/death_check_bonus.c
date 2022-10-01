/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:50:09 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/05/02 00:50:09 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	death_check_sleep(long long time, t_philo *philo)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time <= time)
	{
		if (get_time() - philo->last_eat_time > philo->data->die_time)
		{
			sem_wait(philo->data->printer);
			printf ("%lli %i died\n", get_time() - philo->data->start_time, \
					philo->id);
			sem_close (philo->data->printer);
			sem_close (philo->data->forks);
			free_all(philo->data);
			exit (1);
		}
		usleep(50);
	}
}

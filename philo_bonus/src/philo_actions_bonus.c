/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:50:43 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/05/02 00:50:43 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_fork_lock(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->printer);
	printf ("%lli %i has taken a fork\n", get_time() \
			- philo->data->start_time, philo->id);
	sem_post(philo->data->printer);
	if (philo->data->philo_num == 1)
		death_check_sleep (philo->data->die_time + 1, philo);
	sem_wait(philo->data->forks);
	sem_wait(philo->data->printer);
	printf ("%lli %i has taken a fork\n", get_time() \
			- philo->data->start_time, philo->id);
	sem_post(philo->data->printer);
}

void	philo_fork_unlock(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_eat(t_philo *philo)
{
	philo->last_eat_time = get_time();
	sem_wait(philo->data->printer);
	printf ("%lli %i is eating\n", get_time() \
			- philo->data->start_time, philo->id);
	sem_post(philo->data->printer);
	philo->eat_count++;
	if (philo->eat_count == philo->data->eat_num)
	{
		philo_fork_unlock(philo);
		sem_close (philo->data->printer);
		sem_close (philo->data->forks);
		free_all(philo->data);
		exit (0);
	}
	death_check_sleep(philo->data->eat_time, philo);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->data->printer);
	printf ("%lli %i is sleeping\n", get_time() \
			- philo->data->start_time, philo->id);
	sem_post(philo->data->printer);
	death_check_sleep(philo->data->sleep_time, philo);
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->data->printer);
	printf ("%lli %i is thinking\n", get_time() \
			- philo->data->start_time, philo->id);
	sem_post(philo->data->printer);
	usleep(500);
	while (*(int *)philo->data->forks < 1)
	{
		death_check_sleep(1, philo);
	}
}

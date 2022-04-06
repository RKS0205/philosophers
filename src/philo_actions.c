/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:28:13 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/04/06 02:28:13 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (philo->data->philo_num == 1)
		{
			usleep(philo->data->die_time * 1000);
			return ;
		}
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
		pthread_mutex_lock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is eating\n", get_time() \
					- philo->data->start_time, philo->id);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(philo->data->eat_time * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is sleeping\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->data->dead == 0)
			usleep(philo->data->sleep_time * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->printer);
		if (philo->data->dead == 0)
			printf ("%lli %i is thinking\n", get_time() \
					- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
}

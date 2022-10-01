/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:50:49 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/05/02 00:50:49 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	*philo_func(t_philo *philo)
{
	philo->last_eat_time = get_time();
	if (philo->id % 2 == 0)
		death_check_sleep(philo->data->eat_time, philo);
	while (1)
	{
		philo_fork_lock(philo);
		philo_eat(philo);
		philo_fork_unlock(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	exit (0);
}

static void	wait_processes(t_data *data)
{
	int		status;
	int		n;
	t_philo	*temp;

	n = data->philo_num + 1;
	status = 0;
	while (n-- > 0 && WEXITSTATUS(status) == 0)
		waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		temp = data->philo;
		n = data->philo_num + 1;
		while (n-- > 0)
		{
			kill (temp->process, SIGKILL);
			temp = temp->next;
		}
	}
}

void	start_processes(t_data *data)
{
	int		n;
	t_philo	*temp;

	n = data->philo_num;
	temp = data->philo;
	data->start_time = get_time();
	while (n > 0)
	{
		temp->process = fork();
		if (temp->process == 0)
			philo_func(temp);
		temp = temp->next;
		n--;
	}
	wait_processes(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:27:52 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/04/06 02:27:52 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

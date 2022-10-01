/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:27:58 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/04/06 02:27:58 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf ("Incorrect number of arguments\n");
		return (1);
	}
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf ("Arguments are formatted incorrectly\n");
				return (1);
			}
		}
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_args(argc, argv))
		return (1);
	data = (t_data *) malloc (sizeof(t_data));
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->stop = 0;
	if (argv[5] != NULL)
		data->eat_num = ft_atoi(argv[5]);
	else
		data->eat_num = -1;
	init_philo_list(data);
	start_threads(data);
	free_all(data);
}

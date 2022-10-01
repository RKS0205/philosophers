/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:28:23 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/04/06 02:28:23 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_eat_time;
	int				eat_count;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_philo			*next;
	t_philo			*prev;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	long long		start_time;
	pthread_mutex_t	printer;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	eat_time_mutex;
	int				stop;
	t_philo			*philo;
}	t_data;

int			ft_atoi(const char *nptr);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_fork_unlock(t_philo *philo);
void		philo_fork_lock(t_philo *philo);
long long	get_time(void);
void		free_all(t_data *data);
void		death_check(t_data *data);
void		init_philo_list(t_data *data);
void		death_check(t_data *data);
void		start_threads(t_data *data);
int			check_stop(t_data *data);
int			eat_count_check(t_data *data);
int			check_eat_mutex(t_philo *philo);

#endif
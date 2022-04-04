#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	long long		last_eat_time;
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
	t_philo			*philo;
}	t_data;

int	ft_atoi(const char *nptr);

#endif
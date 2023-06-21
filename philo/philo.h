#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	pthread_t		*th;
	pthread_mutex_t	*fork;
	char 			**pargv;
}				t_philo;


void	thread(t_philo	*philo);
int		ft_error(t_philo *philo);

#endif
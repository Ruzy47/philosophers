#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_philo
{
	pthread_t		*th;
	pthread_mutex_t	mutex;
	char 			**pargv;
}				t_philo;

#endif
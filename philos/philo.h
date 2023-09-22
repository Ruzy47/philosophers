/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/22 12:02:12 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				num;
	pthread_t		th;
	pthread_mutex_t	*fork;
	int				right_fork;
	int				left_fork;
	int				eat_times;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long long int	time_now;
	long long int	time;
}				t_philo;

typedef struct	s_menu
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	t_philo	*philo;
}				t_menu;

int				philo_create(t_menu *menu, t_philo *philo);
int				ft_atoi(const char *str);
int				ft_error(char **argv);
void			*routine(void	*info);
long long int	get_time(t_philo *philo);

#endif
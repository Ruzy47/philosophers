/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/27 17:17:26 by rugrigor         ###   ########.fr       */
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
	pthread_mutex_t	fork[1000];
	int				right_fork;
	int				left_fork;
	int				eat_times;
	int				time_now;
}				t_philo;

typedef struct	s_menu
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_count;
	t_philo	philo[1000];
}				t_menu;

int	philo_create(t_menu *menu, t_philo *philo);
int	ft_atoi(const char *str);
int	ft_error(char **argv);

#endif
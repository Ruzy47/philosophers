/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/15 19:34:15 by rugrigor         ###   ########.fr       */
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
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write;
	int				die;
	int				eat;
	int				eat_times;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meal_count;
	long long		last_meal;
	long long		time;
}				t_philo;

typedef struct	s_menu
{
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int				philo_count;
	int				time_to_die;
	int				die;
	int				eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*eat_t;
	t_philo	*philo;
}				t_menu;

int			philo_create(t_menu *menu);
int			ft_atoi(const char *str);
int			ft_error(char **argv);
void		*routine(void	*info);
long long	get_time(t_philo *philo, int i);
long long	t_time();
void		p_printf(char *str, t_philo *philo);

#endif
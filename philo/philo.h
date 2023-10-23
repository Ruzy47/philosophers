/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/19 17:13:50 by rugrigor         ###   ########.fr       */
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
	pthread_mutex_t	*meal;
	pthread_mutex_t	*last;
	int				*die;
	int				*eat;
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
	pthread_mutex_t	*last;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write;
	t_philo	*philo;
}				t_menu;

int			ft_error(char **argv);
int			ft_atoi(const char *str);
int			fork_create(t_menu *menu);
int			philo_create(t_menu *menu);
void		*routine(void	*info);
void		philo_init(t_menu *menu, int i);
void		p_printf(char *str, t_philo *philo);
void		menu_init(char **argv, t_menu *menu);
void		s_sleep(t_philo *philo, int i, long long n);
long long	t_time();
long long	get_time(t_philo *philo, int i);

#endif
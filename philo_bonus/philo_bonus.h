/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 13:58:28 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				num;
	pthread_t		th;
	pid_t			pid;
	sem_t			*fork;
	sem_t			*write;
	sem_t			*meal;
	sem_t			*last;
	int				die;
	int				eat;
	int				eat_times;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				philo_count;
	int				meal_count;	
	long long		last_meal;
	long long		time;
}				t_philo;

typedef struct s_menu
{
	t_philo			*philo;
	int				philo_count;
}				t_menu;

int			ft_error(char **argv);
int			check2(t_philo *philo);
int			ft_atoi(const char *str);
int			philo_create(t_menu *menu, int i);
void		*routine(t_menu *menu, int i);
void		p_printf(char *str, t_philo *philo);
void		s_sleep(t_philo *philo, int i, long long n);
void		philo_init(t_philo *philo);
void		menu_init(char **argv, t_menu *menu, int i);
long long	t_time(void);
long long	get_time(t_philo *philo, int i);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/17 20:06:25 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	s_sleep(t_philo *philo, int i, long long n)
{
	n = t_time();
	if (i == 1)
	{
		//printf("%lld\n", n);
		
		while (1)
		{
			//printf("aaa");
			if (get_time(philo, 1) - n >= philo->time_to_eat)
					break;
			usleep(20);
		}
		// // pthread_mutex_lock(philo->last);
		// philo->last_meal = get_time(philo, 0);
		// // pthread_mutex_unlock(philo->last);
		// printf("%d\n", philo->num); 
		// printf("%lld\n", philo->last_meal);
	}
	if (i == 0)
	{
		while (1)
		{
			if (get_time(philo, 1) - n >= philo->time_to_sleep)
				break;
			usleep(20);
		}
	}
}

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if ((philo->num - 1) % 2)
		usleep(2000);
	while (*philo->eat == -1 && *philo->die == -1)
	{
		pthread_mutex_lock(philo->left_fork);
		p_printf("take left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		p_printf("take right fork", philo);
		// pthread_mutex_lock(philo->meal);
		// pthread_mutex_unlock(philo->meal);
		pthread_mutex_lock(philo->last);
		s_sleep(philo, 1, 0);
		// pthread_mutex_lock(philo->last);
		p_printf("is eating", philo);
		philo->last_meal = get_time(philo, 0);
		// printf("%d\n", philo->num); 
		// printf("%lld\n", philo->last_meal);
		// pthread_mutex_unlock(philo->last);
		pthread_mutex_unlock(philo->last);
		pthread_mutex_lock(philo->meal);
		philo->eat_times++;
		//printf("%d\n", philo->eat_times);
		pthread_mutex_unlock(philo->meal);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (*philo->eat == 1 || *philo->die == 1)
			break ;
		// pthread_mutex_lock(philo->meal);
		p_printf("is sleeping", philo);
		s_sleep(philo, 0, 0);
		// pthread_mutex_unlock(philo->meal);
		p_printf("is thinking", philo);
	pthread_mutex_unlock(philo->write);	
	}
	//pthread_detath(philo->th);
	return (NULL);
}

int	check(t_menu *menu, int i)
{
	pthread_mutex_lock(menu->last);
	while (++i < menu->philo_count)
		if (get_time(&menu->philo[i], 0) - menu->philo[i].last_meal > menu->time_to_die)
		{
			menu->die = 1;
			// pthread_mutex_lock(menu->philo[0].write);	
			p_printf("is die", &menu->philo[i]);
			pthread_mutex_unlock(menu->last);
			pthread_mutex_lock(menu->philo[0].write);
			return (1);
		}
	pthread_mutex_unlock(menu->last);
	i = 0;
	while (menu->meal_count != -1 && i < menu->philo_count
		&& menu->philo[i].eat_times >= menu->meal_count)
	// {
	// 	if (menu->philo[i].eat_times >= menu->meal_count)
			i++;
		// else
		// 	break ;
		if (i == menu->philo_count)
		{
			pthread_mutex_lock(menu->meal);
			menu->eat = 1;
			// pthread_mutex_lock(menu->philo[0].write);
			printf("[%lld ms] all ate\n", get_time(&menu->philo[0], 0));
			pthread_mutex_unlock(menu->meal);
			// pthread_mutex_unlock(menu->philo[0].write);
			return (1);
		}
	pthread_mutex_unlock(menu->meal);
	return (0);
}

int	philo_create(t_menu *menu)
{
	int	i;
	
	i = -1;
	while (++i < menu->philo_count)
		if (pthread_create(&menu->philo[i].th, NULL, &routine, &menu->philo[i]) == -1)
			return (1);
	while (1)
		if (check(menu, -1) == 1)
			break ;
	// printf("eat : %d\n", menu->eat);
	// printf("die : %d\n", menu->die);
	// printf("die : %d\n", *(menu->philo[0].die));
	i = -1;
	while (++i < menu->philo_count)
	{
		if (pthread_join(menu->philo[i].th, NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < menu->philo_count)
		pthread_mutex_destroy(&(menu->fork[i]));
	pthread_mutex_destroy(menu->write);
	pthread_mutex_destroy(menu->meal);
	// pthread_mutex_unlock(menu->last);
	// pthread_mutex_destroy(menu->last);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:04:59 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 10:19:21 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	unsigned char	*str1;
	int				neg;
	int				num;

	neg = 1;
	if (!str)
		return (0);
	str1 = (unsigned char *) str;
	while (((*str1 >= 9 && *str1 <= 13) || *str1 == ' '))
		str1++;
	if (*str1 == '-' || *str1 == '+')
	{
		if (*str1 == '-')
			neg = -neg;
		str1++;
	}
	if (*str1 < 48 && *str1 > 57)
		return (0);
	num = 0;
	while (*str1 >= 48 && *str1 <= 57)
	{
		num = num * 10 + (*str1 - 48);
		str1++;
	}
	return (num * neg);
}

long long	t_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_time(t_philo *philo, int i)
{
	struct timeval	time;
	long long		t;

	t = 0;
	gettimeofday(&time, NULL);
	if (i == 0)
		t = ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->time);
	if (i == 1)
		t = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (t);
}

void	s_sleep(t_philo *philo, int i, long long n)
{
	n = t_time();
	if (i == 1 && philo->die == -1)
	{
		while (philo->die == -1)
		{
			if (get_time(philo, 1) - n >= philo->time_to_eat)
				break ;
			usleep(50);
		}
	}
	if (i == 0 && philo->die == -1)
	{
		while (philo->die == -1)
		{
			if (get_time(philo, 1) - n >= philo->time_to_sleep)
				break ;
			usleep(50);
		}
	}
}

void	p_printf(char *str, t_philo *philo)
{
	sem_wait(philo->write);
	if (philo->die == -1)
	{
		printf("[%lld ms] %d %s\n", get_time(philo, 0), philo->num, str);
	}
	sem_post(philo->write);
}

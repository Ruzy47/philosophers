/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:04:59 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/25 19:08:29 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static long long	get_time(t_philo *philo)
{
	struct	timeval	time;

	if (philo->time == 0)
	{
		printf("aaa\n");
		gettimeofday(&time, NULL);
		philo->time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		return (0);
	}
	gettimeofday(&time, NULL);
	philo->time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (philo->time_now - philo->time);
}
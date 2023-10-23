/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 16:43:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s3;
	unsigned char	*s4;
	size_t			i;

	i = 0;
	s3 = (unsigned char *) s1;
	s4 = (unsigned char *) s2;
	if (!s1 || !s2)
		return (0);
	if (n == 0 && s3 == NULL && s4 == NULL)
		return (0);
	while (s3[i] && s4[i] && i < n && s3[i] == s4[i])
		i++;
	if (i < n)
		return (s3[i] - s4[i]);
	else
		return (0);
}

int	ft_error(char **argv)
{
	int	i;
	int	y;

	i = 0;
	y = -1;
	while (argv[++i])
	{
		if (ft_strncmp(argv[i], "\0", 1) == 0)
			return (1);
		if (i == 1 && ft_atoi(argv[i]) < 2)
			return (1);
		else if (i != 1 && ft_atoi(argv[i]) < 0)
			return (1);
		y = -1;
		while (argv[i][++y])
		{
			if (argv[i][y] < 48 || argv[i][y] > 57)
				return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/19 16:31:48 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu);
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (fork_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo_init(&menu, -1);
	if (philo_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}
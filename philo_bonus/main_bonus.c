/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 20:17:22 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu);
	if (philo_create(&menu, -1) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:27:48 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/08 18:27:52 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		write (1, "Invalid count of argc\n", 22);
		return (1);
	}
	if (init_info(ac, av, &info) == -1)
	{
		write (1, "invalid input\n", 14);
		return (1);
	}
	start_emulation(&info);
	return (0);
}

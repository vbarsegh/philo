/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:45:25 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/04/30 15:53:35 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

long	my_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (ft_strlen(str) >= 11)
		return (-1);
	if (str[i] == '\0' || (str[i] < '0' || str[i] > '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || res > 2147483647)
		return (-1);
	return (res);
}

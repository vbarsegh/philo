/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:18:38 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/08 18:30:50 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	static long long	start;
	t_timeval			time;

	if (start == 0)
	{
		gettimeofday(&time, NULL);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

void	get_last_eat_time_mutex(t_philo *philo)
{
	sem_wait(philo->info->last_eat_time_sem);
	philo->last_eat_time = get_time();
	sem_post(philo->info->last_eat_time_sem);
}

void	my_usleep(long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
		usleep(500);
}

void	get_last_eat_time_sem(t_philo *philo)
{
	sem_wait(philo->info->last_eat_time_sem);
	philo->last_eat_time = get_time();
	sem_post(philo->info->last_eat_time_sem);
}

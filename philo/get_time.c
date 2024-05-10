/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:30 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/10 14:15:04 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->last_eat_time_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->last_eat_time_mutex);
}

void	my_usleep(t_philo *philo, long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
	{
		if (philo->info->is_died == -1)//sa anum enq vor ete merela bayc sleep-i jmky shat mec el chspasi qni helni,miuangamic prcni cragiry,nu gri died u prcni chspasi el time_to_sleep
			break ;
		usleep(500);
	}
}

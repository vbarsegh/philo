/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:30 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/11 16:46:48 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	static long long	start;
	t_timeval			time;
//start-@ nra hamar vor zapusk taluc tivy 0-ic sksvi,ete chl i start-@ shat mec tvic ksksvi isk et tivy stanum enq gettimeofday funkciayi mijocov,vor veradardznum a en tivy vayrkyanov u mikrovayrkyanov,asyinqn vorpes struct eli
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
	philo->last_eat_time = get_time();//tarmacnum enq verjin hac kerac jamanaky
	pthread_mutex_unlock(&philo->last_eat_time_mutex);
}

void	my_usleep(t_philo *philo, long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
	{
		if (philo->info->is_died == -1)//sa anum enq vor ete merela bayc sleep-i jmky shat mec a ,el chspasi qni helni,miuangamic prcni cragiry,nu gri died u prcni chspasi el time_to_sleep
			break ;
		usleep(500);
	}
}

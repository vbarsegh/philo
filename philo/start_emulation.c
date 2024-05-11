/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_emulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:01 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/11 17:04:07 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_emulation(t_info *info)
{
	int	i;

	i = -1;
	get_time();//esi ete chlini data race enq unenalu vortev sax filoneri hamar start-@ 0a linelu u nuyn jmkum sax philonery dimelu en et startin//sranov nenc enq are vor start-@ arajan vor data racechlni
	while (++i < info->num_of_philos)
		pthread_create(&info->philos[i].tid, NULL,
			(void *)about_philos, &info->philos[i]);//philoner-i qanakaov thread-eri enq bajanaum mer main-@
	while (1)
	{
		if (check_die(info) == -1
			|| eat_all_neccessary_section_of_spagetti(info) == 1)
			break ;
	}
	i = -1;
	while (++i < info->num_of_philos)
	{
		pthread_join(info->philos[i].tid, NULL);
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].last_eat_time_mutex);
		pthread_mutex_destroy(&info->philos[i].current_meal_mutex);
	}
	free(info->philos);
	free(info->forks);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->is_died_mutex);
}

void	*about_philos(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
//qani vor filonery klor krugov en nstac u yur. filo-i aranqnerum enq drvac fork-ery yur. filo unenalu e ir aj ev dzax fork-ery
	left_fork = &philo->info->forks[philo->id];
	right_fork = &philo->info->forks[(philo->id + 1)//hamarakalum enq fork-er@
		% (philo->info->num_of_philos)];

	get_last_eat_time_mutex(philo);//sranov filoneri kyanqi skizbn enq tali
	if ((philo->id + 1) % 2 == 0)
		usleep(500);//bolor zuyg hamarov filonerin qncnum enq vor arajiny kentery vercnen fork-ery,tenc enq anum vor dead lock chunenanq
	while (is_died(philo) != -1)
	{
		if (philo_take_a_forks(philo, left_fork, right_fork) == 1)//es funkcian enqan kkatarvi minchev mi filo chmerni
			return (NULL);
	}
	return (NULL);
}

int	philo_take_a_forks(t_philo *philo,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	print_mutex(philo, "has taken a fork\n");
	if (philo->info->num_of_philos == 1)
	{
		pthread_mutex_unlock(left_fork);
		return (1);
	}
	pthread_mutex_lock(right_fork);
	print_mutex(philo, "has taken a fork\n");
	print_mutex(philo, "is eating\n");
	my_usleep(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	get_last_eat_time_mutex(philo);
	pthread_mutex_lock(&philo->current_meal_mutex);
	philo->current_meal++;
	pthread_mutex_unlock(&philo->current_meal_mutex);
	print_mutex(philo, "is sleeping\n");
	my_usleep(philo, philo->info->time_to_sleep);
	print_mutex(philo, "is thinking\n");
	return (0);
}

void	print_mutex(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (is_died(philo) != -1)
		printf("%lld %d %s", get_time(), philo->id + 1, str);//es if-@ nra  hamar enq stugumm vor ete meky merni el dranic heto inch katarvi printf-ov menq chgrenq et texi unecacy,karan depqer linen vor merneluc heto vorosh filoner hascnenq qnen,het dnen fork-@ ev aylb,es tvarkacners vor printf chanenq if-@ drel enq 
	pthread_mutex_unlock(&philo->info->print_mutex);
}

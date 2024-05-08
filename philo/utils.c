/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:36:41 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/04/30 15:36:42 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(&info->philos[i].last_eat_time_mutex);
		if (get_time() - info->philos[i].last_eat_time >= info->time_to_die)
		{
			pthread_mutex_lock(&info->is_died_mutex);
			info->is_died = -1;
			pthread_mutex_unlock(&info->is_died_mutex);
			pthread_mutex_lock(&info->philos[i].info->print_mutex);
			printf("%lld %d died\n", get_time(), info->philos[i].id + 1);
			pthread_mutex_unlock(&info->philos[i].info->print_mutex);
			pthread_mutex_unlock(&info->philos[i].last_eat_time_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&info->philos[i].last_eat_time_mutex);
		i++;
	}
	return (0);
}

int	eat_all_neccessary_section_of_spagetti(t_info *info)
{
	int	count_philos_which_part_eat_all_neccessaries_spageti;
	int	i;

	if (info->number_of_times_each_philosopher_must_eat < 0)
		return (0);
	count_philos_which_part_eat_all_neccessaries_spageti = 0;
	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(&info->philos[i].current_meal_mutex);
		if (info->philos[i].current_meal
			>= info->number_of_times_each_philosopher_must_eat)
			count_philos_which_part_eat_all_neccessaries_spageti++;
		pthread_mutex_unlock(&info->philos[i].current_meal_mutex);
		i++;
	}
	if (count_philos_which_part_eat_all_neccessaries_spageti
		== info->num_of_philos)
	{
		pthread_mutex_lock(&info->is_died_mutex);
		info->is_died = -1;//es pahy mihate harcnel Narekic
		pthread_mutex_unlock(&info->is_died_mutex);
		return (1);
	}
	return (0);
}

int	is_died(t_philo *philo)
{
	int	is_died;

	pthread_mutex_lock(&philo->info->is_died_mutex);
	is_died = philo->info->is_died;
	pthread_mutex_unlock(&philo->info->is_died_mutex);
	return (is_died);
}

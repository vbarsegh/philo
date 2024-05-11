/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:45:49 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/11 16:42:37 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_and_init_info(int ac, char **av, t_info *info)
{
	info->num_of_philos = my_atol(av[1]);
	if (info->num_of_philos < 1 || info->num_of_philos > 200)
		return (-1);
	info->time_to_die = my_atol(av[2]);
	info->time_to_eat = my_atol(av[3]);
	info->time_to_sleep = my_atol(av[4]);
	if (info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0)
		return (-1);
	info->is_died = 0;//uremn unenq yndhanur struct-um mihat die state ,asem inchi hamar,sax filonery unen arandzin die kargavichak(state) vory hxelu enq et info struct-um gtnvox die-i vra,esi anum enq nra hamar,vor gone mek filo merni dra en info struct-i die-i vichaky ktanq merac,u qani vor sax filoneri die-ery cuyc ein talis et info struct-i die-i vra sax khamarven merac u cragiry kavartenq
	pthread_mutex_init(&info->print_mutex, NULL);
	pthread_mutex_init(&info->is_died_mutex, NULL);//bolor pthread_mutex_init-nery anum enq vor karananq lock u unlock anenq data race-ic xusapelu hamar
	if (ac == 6)
		info->number_of_times_each_philosopher_must_eat = my_atol(av[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6 && info->number_of_times_each_philosopher_must_eat < 0)
		return (-1);
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * (info->num_of_philos));
	if (!info->philos)
		return (-1);
	info->forks = malloc(sizeof(pthread_mutex_t) * (info->num_of_philos));
	if (!info->forks)
	{
		free(info->philos);
		return (-1);
	}
	i = -1;
	while (++i < info->num_of_philos)
	{
		info->philos[i].id = i;
		info->philos[i].current_meal = 0;
		info->philos[i].philo_died = info->is_died;//en verevum grac pahna,vor sax filoneri die-ery hxum enq info struct-i die-i vra vory yndhanura saxi hamar
		info->philos[i].last_eat_time = LLONG_MAX;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].last_eat_time_mutex, NULL);
		pthread_mutex_init(&info->philos[i].current_meal_mutex, NULL);
		info->philos[i].info = info;
	}
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	if (parsing_and_init_info(ac, av, info) == -1)
		return (-1);
	if (init_philo(info) == -1)
		return (-1);
	return (0);
}

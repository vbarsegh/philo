/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:34:58 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/08 18:36:00 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_die(t_philo *philo)
{
	sem_wait(philo->info->last_eat_time_sem);
	if (get_time() - philo->last_eat_time >= philo->info->time_to_die)
	{
		sem_wait(philo->info->is_died_sem);
		philo->info->is_died = -1;
		sem_post(philo->info->is_died_sem);
		sem_wait(philo->info->print_sem);
		printf("%lld %d died\n", get_time(), philo->id + 1);
		sem_post(philo->info->last_eat_time_sem);
		// sem_post(philo->info->print_sem);//esi nra hamnar enq pagum vor miqani filo-i mmernely irar het printf chani,stacvuma vor lock araca u unlock chenq anum ev hajordnery spasman mejen mnum u8 chen karum(hascnum)tpen iranc filo-i mahvan lury,chen hascnum vortev cragiry prccnum enq
		exit(1);
	}
	sem_post(philo->info->last_eat_time_sem);
	return (1);
}

int	eat_all_neccessary_section_of_spagetti(t_philo *philo)
{
	if (philo->info->number_of_times_each_philosopher_must_eat < 0)
		return (0);
	sem_wait(philo->info->current_meal_sem);
	if (philo->current_meal
		== philo->info->number_of_times_each_philosopher_must_eat)
	{
		sem_wait(philo->info->is_died_sem);
		philo->info->is_died = -1;
		sem_post(philo->info->is_died_sem);
		sem_post(philo->info->current_meal_sem);
		exit(0);
	}
	sem_post(philo->info->current_meal_sem);
	return (0);
}

int	is_died(t_philo *philo)
{
	int	is_died;

	sem_wait(philo->info->is_died_sem);
	is_died = philo->info->is_died;
	sem_post(philo->info->is_died_sem);
	return (is_died);
}

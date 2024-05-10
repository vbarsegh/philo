/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_emulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:28:10 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/08 18:30:31 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	func(t_philo *philo)
{
	pthread_create(&philo->tid, NULL, (void *)about_philos, philo);
	get_last_eat_time_sem(philo);//sranov filoneri kyanqi skizbn enq tali
	while (1)
		philo_take_a_forks(philo);
	pthread_join(philo->tid, NULL);
	exit(0);
}

void	start_emulation(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	get_time();//esi ete chlini data race enq unenalu vortev sax filoneri hamar start-@ 0a linelu u nuyn jmkum sax philonery dimelu en et startin//sranov nenc enq are vor start-@ arajan vor data racechlni
	while (++i < info->num_of_philos)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			func(&info->philos[i]);
	}
	i = -1;
	while (++i < info->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < info->num_of_philos)
				kill(info->philos[i].pid, SIGKILL);
			break;//ste xia break,stacvuma vor ete meky merela u sax procesnery es kill em anum,myus procesnerin spasely(waitpid anely), animasta linum,vortev kill ov vochnchacrelem sax processnerin che?dra hamare break vor heklnenq ciklic
		}
	}
	sem_close_and_unlink_func(info);
	free(info->philos);
}

void	*about_philos(t_philo *philo)
{
	while (1)
	{
		if (check_die(philo) == -1
			|| eat_all_neccessary_section_of_spagetti(philo) == 1)
			break ;
	}
	return (NULL);
}

void	philo_take_a_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_sem(philo, "has taken a fork\n");
	sem_wait(philo->info->forks);
	print_sem(philo, "has taken a fork\n");
	print_sem(philo, "is eating\n");
	my_usleep(philo->info->time_to_eat);
	// sem_post(philo->info->forks);
	// sem_post(philo->info->forks);
	get_last_eat_time_sem(philo);
	sem_wait(philo->info->current_meal_sem);
	philo->current_meal++;
	sem_post(philo->info->current_meal_sem);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	print_sem(philo, "is sleeping\n");
	my_usleep(philo->info->time_to_sleep);
	print_sem(philo, "is thinking\n");
}

void	print_sem(t_philo *philo, char *str)
{
	sem_wait(philo->info->print_sem);
	if (is_died(philo) != -1)
		printf("%lld %d %s", get_time(), philo->id + 1, str);
	sem_post(philo->info->print_sem);
}

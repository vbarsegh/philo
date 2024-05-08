#include "philo_bonus.h"

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
	info->is_died = 0;
	if (ac == 6)
		info->number_of_times_each_philosopher_must_eat = my_atol(av[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6 && info->number_of_times_each_philosopher_must_eat < 0)
		return (-1);
	return (0);
}

int	sem_open_function(t_info *info)
{
	info->forks = sem_open("/philos_forks", O_CREAT, 0777, info->num_of_philos);
	info->last_eat_time_sem = sem_open("/last_eat_time_sem",O_CREAT, 0777, 1);
	info->current_meal_sem = sem_open("/current_meal_sem",O_CREAT, 0777, 1);
	info->print_sem = sem_open("/print_sem",O_CREAT, 0777, 1);
	info->is_died_sem = sem_open("/is_died_sem",O_CREAT, 0777, 1);
	if (info->forks == SEM_FAILED || info->last_eat_time_sem == SEM_FAILED 
		|| info->current_meal_sem == SEM_FAILED || info->print_sem == SEM_FAILED
		|| info->is_died_sem == SEM_FAILED)
		return (-1);
	return (0);
}

void	sem_close_and_unlink_func(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->last_eat_time_sem);
	sem_close(info->current_meal_sem);
	sem_close(info->print_sem);
	sem_close(info->is_died_sem);
	sem_unlink("/philos_forks");
	sem_unlink("/last_eat_time_sem");
	sem_unlink("/current_meal_sem");
	sem_unlink("/print_sem");
	sem_unlink("/is_died_sem");
}

int	init_philo(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * (info->num_of_philos));
	if (!info->philos)
		return (-1);
	i = -1;
	while (++i < info->num_of_philos)
	{
		info->philos[i].id = i;
		info->philos[i].current_meal = 0;
		info->philos[i].philo_died = info->is_died;
		info->philos[i].last_eat_time = LLONG_MAX;
		info->philos[i].info = info;
	}
	sem_close_and_unlink_func(info);
	if (sem_open_function(info) == -1)
	{
		free(info->philos);
		return (-1);
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

#include "philo.h"

int	parse_input(int ac, char **av, t_info *info)
{
	info->count_philos = my_atol(av[1]);
	if (info->count_philos < 1 || info->count_philos > 200)
		return(-1);
	info->time_to_die = my_atol(av[2]);
	info->time_to_eat = my_atol(av[3]);
	info->time_to_sleep = my_atol(av[4]);
	if (info->time_to_die < 0 || info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (-1);
	info->is_died = 0;
	pthread_mutex_init(&info->print_mutex, NULL);
	pthread_mutex_init(&info->is_died_mutex, NULL);
	if (ac == 6)
		info->number_of_times_each_philosopher_must_eat = my_atol(av[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	if (info->number_of_times_each_philosopher_must_eat == -1 && ac == 6)
		return (-1);
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	int	i;

	if (parse_input(ac, av, info) == -1)
		return ((-1) && printf("Input arguments is invalid\n"));
	i = -1;
	info->philos = malloc(sizeof(t_philo) * (info->count_philos));
	if (!info->philos)
		return (-1);	
	info->forks = malloc(sizeof(t_info) * (info->count_philos));
	if (!info->forks)
	{
		free(info->philos);
		return (-1);
	}
	while(++i < info->count_philos)
	{
		info->philos[i].id = i;
		info->philos[i].current_meal = 0;
		info->philos[i].last_time_eat = LLONG_MAX;//get_time();//LLONG_MAX;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].current_meal_mutex, NULL);
		pthread_mutex_init(&info->philos[i].last_time_eat_mutex, NULL);
		info->philos[i].is_philo_died = info->is_died;//shat karevora,yur. philo-i mernelu gorcakicy cuyc enq tali info mernelu gorcakci vra vor henc gone mekne merni filoneric sax hamarven merac u cragiry avartvi
		info->philos[i].info = info;//ne ponimayu
	}
	return (0);
}

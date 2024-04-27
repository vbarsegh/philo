#include "philo.h"

void    start_emulation(t_info *info)
{
    int i;

    i = 0;
	get_time();
    while(i < info->count_philos)
    {
        pthread_create(&info->philos[i].tid, NULL, (void *)about_philos, &info->philos[i]);
        i++;
    }
	while(1)
	{
		if (check_die(info) == 1 || eat_all_neccessary_section_of_spagetti(info) == 1)
		{
			break;
		}
	}
	i = 0;
	while(i < info->count_philos)
	{
		pthread_join(info->philos[i].tid, NULL);
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].current_meal_mutex);
		pthread_mutex_destroy(&info->philos[i].last_time_eat_mutex);
		i++;
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

	left_fork = &philo->info->forks[philo->id];
	right_fork = &philo->info->forks[(philo->id + 1) % philo->info->count_philos];
	got_eat_time_mut(philo);
	if ((philo->id + 1) % 2 == 0)//xi +1???
		usleep(500);
	while(is_died(philo) != 1)
	{
		if (take_fork_s(philo, left_fork, right_fork) == 1)
		{
			//got_eat_time_mut(philo);
			return (NULL);
		}
	}
	return (NULL);
}

int	take_fork_s(t_philo *philo, pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork)
{
	pthread_mutex_lock(left_fork);
	mutex_print(philo, "has taken a left fork\n");
	if (philo->info->count_philos == 1)
	{
		pthread_mutex_unlock(left_fork);
		return (1);
	}
	pthread_mutex_lock(right_fork);
	mutex_print(philo, "has taken a right fork\n");
	mutex_print(philo, "philo is eating\n");
	m_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	got_eat_time_mut(philo);//mtacum em vor stex pti lini es funkcian
	pthread_mutex_lock(&philo->current_meal_mutex);
	philo->current_meal++;
	pthread_mutex_unlock(&philo->current_meal_mutex);
	mutex_print(philo, "philo is sleeping\n");
	m_sleep(philo->info->time_to_sleep);
	mutex_print(philo, "philo is thinking\n");
	return (0);
}

void	mutex_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (is_died(philo) != -1)
		printf("%lld %d %s",philo->last_time_eat, philo->id + 1, str);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

int	is_died(t_philo *philo)
{
	int	die;

	pthread_mutex_lock(&philo->info->is_died_mutex);
	die = philo->info->is_died;
	pthread_mutex_unlock(&philo->info->is_died_mutex);
	return (die);
}
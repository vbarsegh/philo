#include "philo.h"

int check_die(t_info *info)
{
	int	i;

	i = -1;
	while(++i < info->count_philos)
	{
		pthread_mutex_lock(&info->philos[i].last_time_eat_mutex);
    	if (get_time() - info->philos[i].last_time_eat >= info->time_to_die)
		{
			pthread_mutex_lock(&info->is_died_mutex);
			info->is_died = -1;
			pthread_mutex_unlock(&info->is_died_mutex);
			pthread_mutex_lock(&info->philos[i].info->print_mutex);
			printf("filo is fall in KOMA\n");
			pthread_mutex_unlock(&info->philos[i].info->print_mutex);
			pthread_mutex_unlock(&info->philos[i].last_time_eat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&info->philos[i].last_time_eat_mutex);
	}
	return (9);
}

long long get_time(void)
{
	static long long start;
	t_timeval time;

	if(start == 0)
	{
		gettimeofday(&time, NULL);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

void	m_sleep(long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
		usleep(500);
}


void	got_eat_time_mut(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_time_eat_mutex);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->last_time_eat_mutex);
}

int	eat_all_neccessary_section_of_spagetti(t_info *info)
{
	int	i;
	int	count;
	
	if (info->number_of_times_each_philosopher_must_eat < 0)
		return (0);
	i = 0;
	count = 0;
	while (i < info->count_philos)
	{
		pthread_mutex_lock(&info->philos[i].current_meal_mutex);
		if (info->philos[i].current_meal == info->number_of_times_each_philosopher_must_eat)
			count++;
		pthread_mutex_unlock(&info->philos[i].current_meal_mutex);
		i++;
	}
	if (count == info->count_philos)
	{
		pthread_mutex_lock(&info->is_died_mutex);
		info->is_died = -1;
		pthread_mutex_unlock(&info->is_died_mutex);
		return (1);
	}
	return (0);
}
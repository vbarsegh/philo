#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
// struct s_philo;
// struct s_info;
typedef struct timeval	t_timeval;
// {
//     time_t tv_sec;     // seconds
//     suseconds_t tv_usec;  // microseconds
// }	t_timeval;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	// pthread_mutex_t	*left;
	// pthread_mutex_t	*right;
	long long		last_time_eat;
	pthread_mutex_t	last_time_eat_mutex;
	int				current_meal;
	pthread_mutex_t	current_meal_mutex;
	struct	s_info	*info;
	int				is_philo_died;
}			t_philo;

typedef struct s_info
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				number_of_times_each_philosopher_must_eat;//limit
	long			count_philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				is_died;
	pthread_mutex_t	is_died_mutex;
}	t_info;

void    start_emulation(t_info *info);
int	init_info(int ac, char **av, t_info *info);
long    my_atol(char *str);
void	*about_philos(t_philo *philo);
int	take_fork_s(t_philo *philo, pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork);
void	mutex_print(t_philo *philo, char *str);
int	is_died(t_philo *philo);
int	parse_input(int ac, char **av, t_info *info);
int check_die(t_info *info);
long long get_time(void);
void	m_sleep(long long time);
void	got_eat_time_mut(t_philo *philo);
int	eat_all_neccessary_section_of_spagetti(t_info *info);

#endif
#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct timeval	t_timeval;
// {
//     time_t tv_sec;     // seconds
//     suseconds_t tv_usec;  // microseconds
// }	t_timeval;

struct s_info;

typedef struct s_philo
{
	int	id;
	pthread_t	tid;
	int	philo_died;
	int	current_meal;
	pthread_mutex_t	current_meal_mutex;
	long long	last_eat_time;
	pthread_mutex_t	last_eat_time_mutex;
	struct	s_info	*info;
}	t_philo;


typedef struct s_info
{
	long			num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				is_died;
	pthread_mutex_t	is_died_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_info;


int check_die(t_info *info);
int	eat_all_neccessary_section_of_spagetti(t_info *info);
void    start_emulation(t_info *info);
void	*about_philos(t_philo *philo);
int	philo_take_a_forks(t_philo *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void	print_mutex(t_philo *philo, char *str);
long long   get_time(void);
void    get_last_eat_time_mutex(t_philo *philo);
void	my_usleep(long long time);
int	ft_strlen(const char *str);
long    my_atol(char *str);
int	parsing_and_init_info(int ac, char **av, t_info *info);
int	init_philo(t_info *info);
int	init_info(int ac, char **av, t_info *info);
int	is_died(t_philo *philo);


#endif
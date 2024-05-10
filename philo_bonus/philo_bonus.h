/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:32:20 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/05/08 18:34:36 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct timeval	t_timeval;
// {
//     time_t tv_sec;     // seconds
//     suseconds_t tv_usec;  // microseconds
// }	t_timeval;

// struct s_info;
typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pid_t			pid;
	int				philo_died;
	int				current_meal;
	long long		last_eat_time;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	long			num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_philo			*philos;
	int				is_died;
	sem_t			*is_died_sem;
	sem_t			*current_meal_sem;// sranq info struct-i mejenq haytararum qani vor stex ete mek filo kerav bavarar chapov spagetin chi spaselu minchev myusnerne uten irenc arjev drvac qanaki chapov,ayl henc meky kerav crgairy avartvelua, vortev parenty chi karanalu hski amen meki arjeqy vortev childerum copy-nernen ,u parenty childi popoxakannerin dostup chuni 
	sem_t			*last_eat_time_sem;//
	sem_t			*forks;
	sem_t			*print_sem;
}	t_info;

int			parsing_and_init_info(int ac, char **av, t_info *info);
int			sem_open_function(t_info *info);
void		sem_close_and_unlink_func(t_info *info);
int			init_philo(t_info *info);
int			init_info(int ac, char **av, t_info *info);
void		func(t_philo *philo);
void		start_emulation(t_info *info);
void		*about_philos(t_philo *philo);
void		philo_take_a_forks(t_philo *philo);
void		print_sem(t_philo *philo, char *str);
int			eat_all_neccessary_section_of_spagetti(t_philo *philo);
int			check_die(t_philo *philo);
int			is_died(t_philo *philo);
long long	get_time(void);
void		get_last_eat_time_sem(t_philo *philo);
void		my_usleep(long long time);
int			ft_strlen(const char *str);
long		my_atol(char *str);

#endif
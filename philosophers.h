/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelienard <noelienard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:51 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/23 17:22:30 by noelienard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_args
{
	int				nbr_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				eat_enough;
	int				start_time;
	int				ready_odd;
	int				philo_died;
	int				nbr_args;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_state;
}					t_args;

typedef struct s_philo
{
	int				last_meal;
	int				nbr_meal;
	int				idx;
	int				i;
	t_args			*args;
	pthread_mutex_t	mtx_meal;
}					t_philo;

void precise_usleep(long duration_ms);

/* main.c */
int					unlock_mutex_fork(t_philo *philo, int fork1, int fork2);
void				create_threads(t_philo *philo, t_args *args);

/* init.c */
int					init_all(t_args *args, char **argv, int nb_args);
int					init_args(t_args *args, char **argv, int nb_args);
t_philo				*init_philo(t_args *args);
pthread_mutex_t		*init_fork(int nbr_p);

/* monitor.c */
void				*ft_monitoring(void *data);
int					check_someone_died(t_philo *lc_philo, int i);
int					check_each_philo(t_philo *lc_philo, int i, int j);

/* routine.c */
void				*action_routine(void *data);

/* action.c */
int					take_fork(t_philo *philo, int fork);

/* action2.c */
int					check_died(t_philo *philo);
int					is_eating(t_philo *philo);

/* utils.c */
int					ft_atoi(char *str);
int					printf_action(t_philo *philo, int timestamp,
						int number_philo, char *str);
int					get_timestamp(void);
int					free_and_destroy_all_mutex(t_args *args, t_philo *philo);

#endif
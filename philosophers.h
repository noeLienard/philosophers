/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:51 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 14:39:09 by nlienard         ###   ########.fr       */
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
}					t_args;

typedef struct s_philo
{
	int				last_meal;
	int				nbr_meal;
	int				idx;
	int				i;
	t_args			*args;
}					t_philo;

/* main.c */
int					init_args(t_args *args, char **argv, int nb_args);
void				*action_routine(void *args);

/* monitor.c */
void				*ft_monitoring(void *data);
int					check_someone_died(t_philo *lc_philo, int i);

/* routine.c */
void				wait_until_end(t_philo *lc_philo, int i);
void				*action_routine(void *data);

/* action.c */
int					take_fork_right(int start_time, t_philo *philo, int i);
int					take_fork_left(int start_time, t_philo *philo, int i);
int					is_eating(int start_time, t_philo *philo, int i);
int					is_sleeping(int start_time, t_philo *philo);
int					is_thinking(int start_time, t_philo *philo);

/* utils.c */
int					ft_atoi(char *str);
int					printf_action(int timestamp, int number_philo, char *str);
int					get_timestamp(void);
int					unlock_mutex(t_philo *philo, int i, int j);
int					free_and_destroy_all_mutex(t_args *args, t_philo *philo);

#endif
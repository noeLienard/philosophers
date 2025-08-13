/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:51 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 13:39:10 by nlienard         ###   ########.fr       */
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

/* action.c */
void				*action_routine(void *args);
void				*ft_monitoring(void *args);

/* utils.c */
int					ft_atoi(char *str);
int					printf_action(int timestamp, int number_philo, char *str);
int					get_timestamp(void);
int					unlock_mutex(t_philo *philo, int i);
#endif
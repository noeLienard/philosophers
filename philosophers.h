/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelienard <noelienard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:51 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/07 18:04:29 by noelienard       ###   ########.fr       */
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

typedef struct s_philo
{
	int				last_meal;
	int				nbr_meal;
	int				idx;
}					t_philo;

typedef struct s_args
{
	int				nbr_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_time;
	int				i;
	t_philo			*tab_philo;
	int				start_time;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	*mtx_print;
}					t_args;

/* main.c */
int					init_args(t_args *args, char **argv, int nb_args);
void				*action_routine(void *args);

/* action.c */
void				*action_routine(void *args);
void				*ft_monitoring(void *lc_args);

/* utils.c */
int					ft_atoi(char *str);
int					printf_action(int timestamp, int number_philo, char *str);
void				fill_tab(t_args *args);
void				free_tab(int *tab);
int					get_timestamp(void);

#endif
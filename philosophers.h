/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:51 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/07 12:11:50 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdbool.h>
# include <errno.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_args
{
	int	nbr_p;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_time;
	int	i;
	int	*tab_philo;
	int	start;
	int	tv_start;
	bool philo_dead;
	pthread_mutex_t	*mtx_fork;
}		t_args;

/* main.c */
int	init_args(t_args *args, char **argv, int nb_args);
void	*action_routine(void *args);

/* action.c */
void	is_eating(t_args *lc_args, int i);
void	is_sleeping(t_args *lc_args, int i);
void	is_thinking(t_args *lc_args, int i);
void	*action_routine(void *args);

/* utils.c */
int		ft_atoi(char *str);
int		printf_action(int timestamp, int number_philo, char *str);
void	fill_tab(t_args *args);
void	free_tab(int *tab);
int		get_timestamp(void);

#endif
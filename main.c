/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/07/18 15:40:33 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	printf("%zu\n", args.nbr_p);
	printf("%zu\n", args.time_to_die);
	printf("%zu\n", args.time_to_eat);
	printf("%zu\n", args.time_to_sleep);
	printf("%zu\n", args.nbr_time);
*/
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]);
	args->time_to_eat = ft_atoi(argv[2]);
	args->time_to_sleep = ft_atoi(argv[3]);
	args->tab_philo1 = malloc(sizeof(int) * (args->nbr_p / 2));
	args->tab_philo2 = malloc(sizeof(int) * (args->nbr_p / 2));
	if (nb_args == 6)
		args->nbr_time = ft_atoi(argv[4]);
}

void	*action_routine(void *args)
{
	struct timeval	tv;
	t_args			*lc_args;
	
	lc_args = (t_args *)args;
	pthread_mutex_lock(&mutex);
	/*taken fork*/
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "has taken a fork");
	/*Is eating*/
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "is eating");
	//printf("%d\n", lc_args->time_to_eat);
	usleep(lc_args->time_to_eat);
	pthread_mutex_unlock(&mutex);
	/*Is Sleeping*/
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "is sleeping");
	usleep(lc_args->time_to_sleep);
	/*Is Thinking*/
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "is thinking");
	usleep(lc_args->time_to_die);
	return (NULL);
}

void	create_threads(t_args *args)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, action_routine, args);
	pthread_join(tid, NULL);
}

int	main(int argc, char **argv)
{
	t_args	args;

	init_args(&args, &argv[1], argc);
	fill_tab(&args);
	create_threads(&args);
	//free(args.tab_philo1);
	//free(args.tab_philo2);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/07/17 15:07:37 by nlienard         ###   ########.fr       */
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
pthread_mutex_t    mutex = PTHREAD_MUTEX_INITIALIZER;


void	fill_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]);
	args->time_to_eat = ft_atoi(argv[2]);
	args->time_to_sleep = ft_atoi(argv[3]);
	if (nb_args == 6)
		args->nbr_time = ft_atoi(argv[4]);
}

void	*action_routine(void *args)
{
	(void)args;
	struct timeval tv;
	int timestamp;

	timestamp = gettimeofday(&tv, NULL);
	// if (timestamp == -1)
	// 	return ;
	printf_action(tv.tv_usec, 1, "has taken a fork");
	timestamp = gettimeofday(&tv, NULL);
	pthread_mutex_lock(&mutex);
	printf_action(tv.tv_usec, 1, "is eating");
	pthread_mutex_unlock(&mutex);
	timestamp = gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "is sleeping");
	timestamp = gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, 1, "is thinking");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args args;
	pthread_t	tid;

	fill_args(&args, &argv[1], argc);
	pthread_create(&tid, NULL, action_routine, NULL);
    pthread_join(tid, NULL);
	return (0);
}

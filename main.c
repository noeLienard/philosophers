/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/06 14:46:02 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]);
	args->time_to_eat = ft_atoi(argv[2]);
	args->time_to_sleep = ft_atoi(argv[3]);
	if (nb_args == 6)
		args->nbr_time = ft_atoi(argv[4]);
	args->tab_philo = malloc(sizeof(int *) * args->nbr_p);
	args->is_die = 0;
	args->nbr_fork = ft_atoi(argv[0]);
}

void	create_threads(t_args args)
{
	pthread_t	tid[args.nbr_p];

	args.i = 0;
	while (args.i < args.nbr_p)
	{
		pthread_create(&tid[args.i], NULL, action_routine, &args);
		args.i++;
	}
	args.i = 0;
	while (args.i < args.nbr_p)
	{
		pthread_join(tid[args.i], NULL);
		args.i++;
	}
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (1);
	init_args(&args, &argv[1], argc);
	fill_tab(&args);
	create_threads(args);
	return (0);
}

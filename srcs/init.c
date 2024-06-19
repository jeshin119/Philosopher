/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:20 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 14:56:14 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_argumnets(int ac, char **av, t_args *args)
{
	if (ac != 5 && ac != 6)
		exit(EXIT_FAILURE);
	args->number = ft_atoi(av[1]);
	if (args->number < 0)
		exit(EXIT_FAILURE);
	args->time_to_die = ft_atoi(av[2]);
	if (args->time_to_die < 0)
		exit(EXIT_FAILURE);
	args->time_to_eat = ft_atoi(av[3]);
	if (args->time_to_eat < 0)
		exit(EXIT_FAILURE);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->time_to_sleep < 0)
		exit(EXIT_FAILURE);
	if (av[5] != NULL)
	{
		args->must_eat_times = ft_atoi(av[5]);
		if (args->must_eat_times < 0)
			exit(EXIT_FAILURE);
	}
	else
		args->must_eat_times = -1;
}

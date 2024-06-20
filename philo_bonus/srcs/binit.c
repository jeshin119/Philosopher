/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 15:37:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static void	init_philo_tab(t_info *info)
{
	info->philo_tab = (int *)malloc(sizeof(int) * info->args->number);
	if (info->philo_tab == 0)
		handle_error("malloc philo_tab");
	memset(info->philo_tab, 0, sizeof(int) * info->args->number);
}

static void	init_fork_tab(t_info *info)
{
	int	size;

	size = info->args->number;
	info->fork_tab = (int *)malloc(sizeof(int) * size);
	if (info->fork_tab == 0)
		handle_error("malloc fork_tab");
	memset(info->fork_tab, 0, sizeof(int) * size);
}

static void	init_argumnets(int ac, char **av, t_args *args)
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

int	init_info(int ac, char **av, t_args *args, t_info *info)
{
	init_argumnets(ac, av, args);
	info->args = args;
	init_philo_tab(info);
	init_fork_tab(info);
	sem_open("pb",O_CREAT | O)
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

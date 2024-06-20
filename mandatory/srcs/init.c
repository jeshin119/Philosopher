/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 11:56:45 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_pth_tab(t_info *info)
{
	info->pth_tab = (t_pth *)malloc(sizeof(t_pth) * info->args->number);
	if (info->pth_tab == 0)
		handle_error("malloc pth_tab");
	memset(info->pth_tab, 0, sizeof(t_pth) * info->args->number);
}

static void	init_mutex_tab(t_info *info)
{
	int	size;
	int	i;

	size = info->args->number;
	info->mutex_tab = malloc(sizeof(pthread_mutex_t) * size);
	if (info->mutex_tab == 0)
		handle_error("malloc mutex_tab");
	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(&(info->mutex_tab[i]), NULL))
			handle_error("init mutex");
	}
	if (pthread_mutex_init(&(info->lock), NULL))
		handle_error("init mutex");
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

static int	init_argumnets(int ac, char **av, t_args *args)
{
	if (ac != 5 && ac != 6)
		return (EXIT_FAILURE);
	args->number = ft_atoi(av[1]);
	if (args->number < 0)
		return (EXIT_FAILURE);
	args->time_to_die = ft_atoi(av[2]);
	if (args->time_to_die < 0)
		return (EXIT_FAILURE);
	args->time_to_eat = ft_atoi(av[3]);
	if (args->time_to_eat < 0)
		return (EXIT_FAILURE);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (av[5] != NULL)
	{
		args->must_eat_times = ft_atoi(av[5]);
		if (args->must_eat_times < 0)
			return (EXIT_FAILURE);
	}
	else
		args->must_eat_times = -1;
	return (EXIT_SUCCESS);
}

int	init_info(int ac, char **av, t_args *args, t_info *info)
{
	if (init_argumnets(ac, av, args))
		return (EXIT_FAILURE);
	info->args = args;
	init_pth_tab(info);
	init_fork_tab(info);
	init_mutex_tab(info);
	gettimeofday(&(info->starttime), NULL);
	info->prior = 1;
	return (EXIT_SUCCESS);
}

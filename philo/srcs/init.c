/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:52:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/23 18:52:53 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_tab(t_info *info)
{
	int	i;

	info->pth_tab = (t_pth *)malloc(sizeof(t_pth) * info->args->number);
	if (info->pth_tab == 0)
		handle_error("malloc pth_tab");
	memset(info->pth_tab, 0, sizeof(t_pth) * info->args->number);
	info->fork_tab = (int *)malloc(sizeof(int) * info->args->number);
	if (info->fork_tab == 0)
		handle_error("malloc fork_tab");
	memset(info->fork_tab, 0, sizeof(int) * info->args->number);
	info->mutex_tab = malloc(sizeof(pthread_mutex_t) * info->args->number);
	if (info->mutex_tab == 0)
		handle_error("malloc mutex_tab");
	i = -1;
	while (++i < info->args->number)
	{
		if (pthread_mutex_init(&(info->mutex_tab[i]), NULL))
			handle_error("init mutex");
	}
}

static int	init_argumnets(char **av, t_args *args)
{
	args->number = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
	{
		args->must_eat_times = ft_atoi(av[5]);
		if (args->must_eat_times == 0)
			return (EXIT_FAILURE);
	}
	else
		args->must_eat_times = -1;
	return (EXIT_SUCCESS);
}

static int	chk_arguments(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	init_info(int ac, char **av, t_args *args, t_info *info)
{
	if (chk_arguments(ac, av))
		return (EXIT_FAILURE);
	if (init_argumnets(av, args))
		return (EXIT_FAILURE);
	info->args = args;
	info->enough = 0;
	info->end = 0;
	init_tab(info);
	if (pthread_mutex_init(&(info->lock), NULL))
		handle_error("init mutex");
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:20 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:45:27 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_argumnets(int ac, char **av, t_args *args)
{
	
	if (ac < 5 || ac > 6)
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

static void	init_pth_tab(t_info *info)
{
	info->pth_tab = (t_pth *)malloc(sizeof(t_pth) * info->args->number);
	if (info->pth_tab == 0)
		handle_error("malloc pth_tab");
	memset(info->pth_tab, 0, sizeof(t_pth) * info->args->number);
}

static void	init_mutex_tab(t_info *pinfo)
{
	int	size;
	int	i;

	size = pinfo->args->number;
	pinfo->mutex_tab = malloc(sizeof(pthread_mutex_t) * size);
	if (pinfo->mutex_tab == 0)
		handle_error("malloc mutex_tab");
	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(&(pinfo->mutex_tab[i]), NULL))
			handle_error("init mutex");
	}
}

static void	init_fork_tab(t_info *pinfo)
{
	int	size;

	size = pinfo->args->number;
	pinfo->fork_tab = (int *)malloc(sizeof(int) * size);
	if (pinfo->fork_tab == 0)
		handle_error("malloc fork_tab");
	memset(pinfo->fork_tab, 0, sizeof(int) * size);
}

void	init_info(t_args *args, t_info *info)
{
	int	i;

	info->args = args;
	gettimeofday(&(info->starttime), NULL);
	init_pth_tab(info);
	init_fork_tab(info);
	init_mutex_tab(info);
}

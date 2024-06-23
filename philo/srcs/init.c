/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/23 17:49:40 by jeshin           ###   ########.fr       */
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
	if (pthread_mutex_init(&(info->lock), NULL))
		handle_error("init mutex");
}

static void	init_argumnets(char **av, t_args *args)
{
	args->number = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		args->must_eat_times = ft_atoi(av[5]);
	else
		args->must_eat_times = -1;
}

static void	chk_arguments(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		exit(EXIT_FAILURE);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				exit(EXIT_FAILURE);
		}
	}
}

int	init_info(int ac, char **av, t_args *args, t_info *info)
{
	chk_arguments(ac, av);
	init_argumnets(av, args);
	info->args = args;
	init_tab(info);
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

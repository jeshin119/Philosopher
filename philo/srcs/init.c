/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:52:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/24 17:06:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	malloc_tab(t_info *info)
{
	info->pth_tab = (t_pth *)malloc(sizeof(t_pth) * info->args->number);
	if (info->pth_tab == 0)
		return (handle_error("malloc pth_tab"));
	info->fork_tab = (int *)malloc(sizeof(int) * info->args->number);
	if (info->fork_tab == 0)
	{
		free(info->pth_tab);
		return (handle_error("malloc fork_tab"));
	}
	info->mutex_tab = malloc(sizeof(pthread_mutex_t) * info->args->number);
	if (info->mutex_tab == 0)
	{
		free(info->pth_tab);
		free(info->fork_tab);
		return (handle_error("malloc mutex_tab"));
	}
	memset(info->pth_tab, 0, sizeof(t_pth) * info->args->number);
	memset(info->fork_tab, 0, sizeof(int) * info->args->number);
	return (EXIT_SUCCESS);
}

static int	init_membervariable(char **av, t_args *args, t_info *info)
{
	args->number = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->must_eat_times = -1;
	if (av[5] != NULL)
	{
		args->must_eat_times = ft_atoi(av[5]);
		if (args->must_eat_times == 0)
			return (EXIT_FAILURE);
	}
	info->args = args;
	info->enough = 0;
	info->end = 0;
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

int	mutex_init(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->args->number)
	{
		if (pthread_mutex_init(&(info->mutex_tab[i]), NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(info->mutex_tab[j]));
			free(info->pth_tab);
			free(info->fork_tab);
			free(info->mutex_tab);
			return (handle_error("init mutex"));
		}
	}
	if (pthread_mutex_init(&(info->mend), NULL))
		return (handle_error("init mutex"));
	if (pthread_mutex_init(&(info->mprt), NULL))
		return (handle_error("init mutex"));
	return (EXIT_SUCCESS);
}

int	init_info(int ac, char **av, t_args *args, t_info *info)
{
	if (chk_arguments(ac, av))
		return (EXIT_FAILURE);
	if (init_membervariable(av, args, info))
		return (EXIT_FAILURE);
	if (malloc_tab(info))
		return (EXIT_FAILURE);
	if (mutex_init(info))
		return (EXIT_FAILURE);
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

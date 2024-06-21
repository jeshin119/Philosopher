/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/21 20:22:25 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

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

static void	init_arguments(int ac, char **av, t_info *info)
{
	info->number = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		info->must_eat_times = ft_atoi(av[5]);
	else
		info->must_eat_times = -1;
}

static void	init_sem(t_info *info)
{
	sem_unlink("/fork");
	sem_unlink("/whodead");
	sem_unlink("/eatingend");
	info->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, info->number);
	if (info->fork == SEM_FAILED)
		handle_error("sem open: ");
	info->whodead = sem_open("/whodead", O_CREAT | O_EXCL, 0644, 0);
	if (info->whodead == SEM_FAILED)
		handle_error("sem open: ");
	info->eatingend = sem_open("/eatingend", O_CREAT | O_EXCL, 0644, 0);
	if (info->eatingend == SEM_FAILED)
		handle_error("sem open: ");
}

static void	init_philos(t_info *info)
{
	info->ptab = (t_philo *)malloc(sizeof(t_philo) * info->number);
	if (info->ptab == 0)
		handle_error("malloc: ");
	memset(info->ptab, 0, sizeof(t_philo) * info->number);
}

int	init_info(int ac, char **av, t_info *info)
{
	chk_arguments(ac, av);
	init_arguments(ac, av, info);
	init_sem(info);
	init_philos(info);
	info->enough = 0;
	info->status = 0;
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

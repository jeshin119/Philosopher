/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 20:20:20 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static void	init_argumnets(int ac, char **av, t_info *info)
{
	if (ac != 5 && ac != 6)
		exit(EXIT_FAILURE);
	info->number = ft_atoi(av[1]);
	if (info->number < 0)
		exit(EXIT_FAILURE);
	info->time_to_die = ft_atoi(av[2]);
	if (info->time_to_die < 0)
		exit(EXIT_FAILURE);
	info->time_to_eat = ft_atoi(av[3]);
	if (info->time_to_eat < 0)
		exit(EXIT_FAILURE);
	info->time_to_sleep = ft_atoi(av[4]);
	if (info->time_to_sleep < 0)
		exit(EXIT_FAILURE);
	if (av[5] != NULL)
	{
		info->must_eat_times = ft_atoi(av[5]);
		if (info->must_eat_times < 0)
			exit(EXIT_FAILURE);
	}
	else
		info->must_eat_times = -1;
}

static void	init_sem(t_info *info)
{
	if (sem_unlink("/fork"))
		handle_error("sem_unlink: ");
	if (sem_unlink("/whodead"))
		handle_error("sem_unlink: ");
	if (sem_unlink("/endeating"))
		handle_error("sem_unlink: ");
	info->fork = sem_open("/fork", O_CREAT | O_EXCL , 0644, info->number);
	if (info->fork ==SEM_FAILED)
		handle_error("sem open: ");
	info->whodead = sem_open("/whodead", O_CREAT | O_EXCL , 0644, 0);
	if (info->whodead == SEM_FAILED)
		handle_error("sem open: ");
	info->endeating = sem_open("/endeating", O_CREAT | O_EXCL , 0644, 0);
	if (info->endeating == SEM_FAILED)
		handle_error("sem open: ");
}

int	init_info(int ac, char **av, t_info *info)
{
	init_argumnets(ac, av, info);
	init_sem(info);
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}

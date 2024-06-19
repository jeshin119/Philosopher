/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 14:56:02 by jeshin           ###   ########.fr       */
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
	pinfo->fork_tab = (t_fork *)malloc(sizeof(t_fork) * size);
	if (pinfo->fork_tab == 0)
		handle_error("malloc fork_tab");
	memset(pinfo->fork_tab, 0, sizeof(t_fork) * size);
}

static void	init_start_time(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->args->number)
		gettimeofday(&((info->pth_tab)[i].atetime), NULL);
	gettimeofday(&(info->starttime), NULL);
}

void	init_info(t_args *args, t_info *info)
{
	int	i;

	info->args = args;
	init_pth_tab(info);
	init_fork_tab(info);
	init_mutex_tab(info);
	init_start_time(info);
}

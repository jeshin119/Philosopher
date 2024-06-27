/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:49:16 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/27 20:57:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	hold_fork(t_pth *pth, int left, int right)
{
	pthread_mutex_lock(&(pth->info->mutex_tab[left]));
	(pth->info->fork_tab)[left] = ON;
	if (prt_status(pth, 1))
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_lock(&(pth->info->mutex_tab[right]));
	(pth->info->fork_tab)[right] = ON;
	if (prt_status(pth, 1))
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

static int	putdown_fork(t_pth *pth, int left, int right)
{
	pthread_mutex_lock(&(pth->info->mutex_tab[left]));
	(pth->info->fork_tab)[left] = OFF;
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_lock(&(pth->info->mutex_tab[right]));
	(pth->info->fork_tab)[right] = OFF;
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

int	set_left_right(int *left, int *right, t_pth *pth)
{
	*left = pth->name - 1;
	if (pth->name == pth->info->args->number)
		*right = 0;
	else
		*right = pth->name;
	return (EXIT_SUCCESS);
}

static int	eating(t_pth *pth, int left, int right)
{
	long	curtime;

	curtime = get_time(pth);
	while (get_time(pth) <= curtime + pth->info->args->time_to_eat)
	{
		usleep(100);
		if (chk_dead(pth) == TRUE)
		{
			putdown_fork(pth, left, right);
			return (END);
		}
	}
	pth->atetime = get_time(pth);
	pth->atecnt++;
	return (EXIT_SUCCESS);
}

int	eat(int left, int right, t_pth *pth)
{
	usleep(100);
	if (chk_dead(pth) == TRUE)
		return (END);
	if (chk_eat(pth, left, right))
		return (EXIT_FAILURE);
	if (hold_fork(pth, left, right))
		return (END);
	if (prt_status(pth, 2))
		return (END);
	if (eating(pth, left, right))
		return (END);
	if (chk_atecnt(pth))
		return (END);
	putdown_fork(pth, left, right);
	return (EXIT_SUCCESS);
}

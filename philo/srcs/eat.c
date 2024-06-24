/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:49:16 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/23 19:01:02 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	hold_fork(t_pth *pth, int left, int right)
{
	if (pthread_mutex_lock(&(pth->info->mutex_tab[left])))
		handle_error("mutex lock: ");
	if (pthread_mutex_lock(&(pth->info->mutex_tab[right])))
		handle_error("mutex lock: ");
	printf("%ld %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[left] = ON;
	printf("%ld %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[right] = ON;
	return (EXIT_SUCCESS);
}

static int	putdown_fork(t_pth *pth, int left, int right)
{
	(pth->info->fork_tab)[right] = OFF;
	(pth->info->fork_tab)[left] = OFF;
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
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

int	eat(int left, int right, t_pth *pth)
{
	long	curtime;

	if (pth->info->fork_tab[left] == ON | pth->info->fork_tab[right] == ON)
		return (EXIT_FAILURE);
	hold_fork(pth, left, right);
	curtime = get_time(pth);
	printf("%ld %d is eating\n", curtime, pth->name);
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
	chk_atecnt(pth);
	putdown_fork(pth, left, right);
	return (EXIT_SUCCESS);
}

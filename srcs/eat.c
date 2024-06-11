/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:09:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	eat(t_pth *pth)
{
	gettimeofday(&(pth->atetime), NULL);
	printf("%ld %d is eating\n", \
	(pth->atetime.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(pth->atetime.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	pth->ate_times++;
	usleep(pth->info->args->time_to_eat * 1000);
	return (EXIT_SUCCESS);
}

static int	hold_left(t_pth *pth, int left)
{
	struct timeval	t;

	if (pthread_mutex_lock(&((pth->info->mutex_tab)[left])))
		return (EXIT_FAILURE);
	gettimeofday(&t, NULL);
	printf("%ld %d has taken a fork\n", \
	(t.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	(pth->info->fork_tab)[left] = 1;
	return (EXIT_SUCCESS);
}

static int	hold_right(t_pth *pth, int right)
{
	struct timeval	t;

	if (pthread_mutex_lock(&((pth->info->mutex_tab)[right])))
		return (EXIT_FAILURE);
	gettimeofday(&t, NULL);
	printf("%ld %d has taken a fork\n", \
	(t.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	(pth->info->fork_tab)[right] = 1;
	return (EXIT_SUCCESS);
}

static int	chk_must_eat_times(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (FALSE);
	if (pth->ate_times >= pth->info->args->must_eat_times)
		return (TURE);
	return (FALSE);
}

int	try_eat(t_pth *pth)
{
	int	left;
	int	right;

	left = pth->name - 1;
	if (chk_must_eat_times(pth) == TURE)
		return (EXIT_SUCCESS);
	if (pth->name == pth->info->args->number + 1)
		right = 0;
	else
		right = pth->name;
	if (hold_left(pth, left))
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
		return (EXIT_FAILURE);
	}
	if (hold_right(pth, right))
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
		return (EXIT_FAILURE);
	}
	eat(pth);
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

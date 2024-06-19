/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 17:16:43 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	hold_fork(t_pth *pth, int left, int right)
{
	if (pthread_mutex_lock(&(pth->info->mutex_tab[left])))
		handle_error("mutex lock: ");
	if (pthread_mutex_lock(&(pth->info->mutex_tab[right])))
		handle_error("mutex lock: ");
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[left].who_ate = pth->name;
	(pth->info->fork_tab)[left].is_locked = ON;
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[right].who_ate = pth->name;
	(pth->info->fork_tab)[right].is_locked = ON;
	return (EXIT_SUCCESS);
}

static int	putdown_fork(t_pth *pth, int left, int right)
{
	(pth->info->fork_tab)[left].is_locked = OFF;
	(pth->info->fork_tab)[right].is_locked = OFF;
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	return (EXIT_SUCCESS);
}

static int	set_left_right(int *left, int *right, t_pth *pth)
{
	*left = pth->name - 1;
	if (pth->name == pth->info->args->number)
		*right = 0;
	else
		*right = pth->name;
	return (EXIT_SUCCESS);
}

static int	eat(int left, int right, t_pth *pth)
{
	int	curtime;

	if (pth->info->fork_tab[left].is_locked == ON | pth->info->fork_tab[right].is_locked == ON)
		return (EXIT_FAILURE);
	hold_fork(pth, left, right);
	curtime = get_time(pth);
	printf("%d %d is eating\n", curtime, pth->name);
	while (get_time(pth) <= curtime + pth->info->args->time_to_eat)
		usleep(100);
	gettimeofday(&(pth->atetime), NULL);
	pth->ate_times++;
	putdown_fork(pth, left, right);
	return (EXIT_SUCCESS);
}

int	try_eat(t_pth *pth)
{
	int	left;
	int	right;

	set_left_right(&left, &right, pth);
	if (chk_equal(pth, left, right))
		return (EXIT_FAILURE);
	eat(left, right, pth);
	return (EXIT_SUCCESS);
}

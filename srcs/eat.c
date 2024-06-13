/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/13 17:50:16 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	hold_fork(t_pth *pth, int left, int right)
{
	if (pthread_mutex_lock(&(pth->info->mutex_tab[left])))
		handle_error("hold fork 1mutex lock: ");
	if (pthread_mutex_lock(&(pth->info->mutex_tab[right])))
		handle_error("hold fork 2mutex lock: ");
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[left].num = pth->name;
	(pth->info->fork_tab)[left].is_locked = ON;
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[right].num = pth->name;
	(pth->info->fork_tab)[right].is_locked = ON;
	return (EXIT_SUCCESS);
}

int	putdown_fork(t_pth *pth, int left, int right)
{
	(pth->info->fork_tab)[left].is_locked = OFF;
	(pth->info->fork_tab)[right].is_locked = OFF;
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

static int	eat(int left, int right, t_pth *pth)
{
	if (pth->info->fork_tab[left].is_locked == ON | pth->info->fork_tab[right].is_locked == ON)
		return (EXIT_FAILURE);
	hold_fork(pth, left, right);
	printf("%d %d is eating\n", get_time(pth), pth->name);
	pth->ate_times++;
	usleep(pth->info->args->time_to_eat * 1000);
	gettimeofday(&(pth->atetime), NULL);
	putdown_fork(pth, left, right);
	return (EXIT_SUCCESS);
}

int	try_eat(t_pth *pth)
{
	int	left;
	int	right;

	if (is_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	if (chk_musteat_times(pth))
		return (EXIT_FAILURE);
	if (set_left_right(&left, &right, pth))
		return (EXIT_SUCCESS);
	if (chk_equal(pth, left, right))
		return (EXIT_SUCCESS);
	eat(left, right, pth);
	return (EXIT_SUCCESS);
}

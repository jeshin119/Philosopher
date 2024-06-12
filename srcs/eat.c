/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/12 18:26:41 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	hold_left(t_pth *pth, int left)
{
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[left] = 1;
	return (EXIT_SUCCESS);
}

static int	hold_right(t_pth *pth, int right)
{
	printf("%d %d has taken a fork\n", get_time(pth), pth->name);
	(pth->info->fork_tab)[right] = 1;
	return (EXIT_SUCCESS);
}

static int	eat(int left, int right, t_pth *pth)
{
	if (pthread_mutex_lock(&((pth->info->mutex_tab)[left])))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&((pth->info->mutex_tab)[right])))
		return (EXIT_FAILURE);
	hold_left(pth, left);
	hold_right(pth, right);
	printf("%d %d is eating\n", get_atetime(pth), pth->name);
	pth->ate_times++;
	usleep(pth->info->args->time_to_eat * 1000);
	return (EXIT_SUCCESS);
}

int	try_eat(t_pth *pth)
{
	int	left;
	int	right;

	if (chk_musteat_times(pth))
		return (EXIT_FAILURE);
	if (chk_equal(pth))
		return (EXIT_FAILURE);
	if (chk_left_right(&left, &right, pth))
		return (EXIT_FAILURE);
	eat(left, right, pth);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/13 17:56:22 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	chk_musteat_times(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (pth->ate_times >= pth->info->args->must_eat_times)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_left_right(int *left, int *right, t_pth *pth)
{
	if (pth->info->args->number <= 1)
		return (EXIT_FAILURE);
	*left = pth->name - 1;
	if (pth->name == pth->info->args->number)
		*right = 0;
	else
		*right = pth->name;
	return (EXIT_SUCCESS);
}

int	chk_equal(t_pth *pth, int left, int right)
{
	if (pth->info->fork_tab[left].is_locked == ON | pth->info->fork_tab[right].is_locked == ON)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&(pth->info->mutex_tab[left])))
		handle_error("mutex lock: ");
	if (pthread_mutex_lock(&(pth->info->mutex_tab[right])))
		handle_error("mutex lock: ");
	if ((pth->info->fork_tab)[left].num == pth->name && (pth->info->fork_tab)[right].num == pth->name)
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
		pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

int	is_dead(t_pth *pth)
{
	int	curtime;
	int	atetime;
	int	dietime;

	curtime = get_time(pth);
	atetime = get_atetime(pth);
	dietime = pth->info->args->time_to_die;
	if (curtime - atetime >= dietime)
	{
		die(pth);
		return (TRUE);
	}
	return (FALSE);
}

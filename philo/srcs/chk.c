/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/27 20:55:15 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	chk_atecnt(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (pth->atecnt == pth->info->args->must_eat_times)
	{
		pthread_mutex_lock(&(pth->info->mend));
		(pth->info->enough)++;
		if (pth->info->enough == pth->info->args->number)
		{
			pthread_mutex_unlock(&(pth->info->mend));
			if (prt_status(pth, 5))
				return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&(pth->info->mend));
	}
	return (EXIT_SUCCESS);
}

int	chk_eat(t_pth *pth, int left, int right)
{
	pthread_mutex_lock(&(pth->info->mutex_tab[left]));
	if (pth->info->fork_tab[left] == ON)
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&((pth->info->mutex_tab)[left]));
	pthread_mutex_lock(&(pth->info->mutex_tab[right]));
	if (pth->info->fork_tab[right] == ON)
	{
		pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&((pth->info->mutex_tab)[right]));
	return (EXIT_SUCCESS);
}

int	chk_dead(t_pth *pth)
{
	long	curtime;
	long	dietime;

	pthread_mutex_lock(&(pth->info->mend));
	if (pth->info->end == ON)
	{
		pthread_mutex_unlock(&(pth->info->mend));
		return (TRUE);
	}
	pthread_mutex_unlock(&(pth->info->mend));
	curtime = get_time(pth);
	dietime = pth->info->args->time_to_die;
	if (curtime - pth->atetime >= dietime)
	{
		if (prt_status(pth, 4))
			return (TRUE);
		pthread_mutex_lock(&(pth->info->mend));
		pth->info->end = ON;
		pthread_mutex_unlock(&(pth->info->mend));
		return (TRUE);
	}
	return (FALSE);
}

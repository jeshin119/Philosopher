/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/27 20:55:14 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	_sleep(t_pth *pth)
{
	int	curtime;

	usleep(100);
	if (chk_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	curtime = get_time(pth);
	if (prt_status(pth, 3))
		return (EXIT_FAILURE);
	while (get_time(pth) <= curtime + pth->info->args->time_to_sleep)
	{
		usleep(100);
		if (chk_dead(pth) == TRUE)
			return (EXIT_FAILURE);
	}
	pth->think = 0;
	return (EXIT_SUCCESS);
}

int	think(t_pth *pth)
{
	usleep(100);
	if (chk_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	if (pth->think == 1)
		return (EXIT_SUCCESS);
	if (prt_status(pth, 0))
		return (EXIT_FAILURE);
	pth->think = 1;
	return (EXIT_SUCCESS);
}

static void	prt_status_msg(t_pth *pth, int which)
{
	if (which == 0)
		printf("%ld %d is thinking\n", get_time(pth), pth->name);
	else if (which == 1)
		printf("%ld %d has taken a fork\n", get_time(pth), pth->name);
	else if (which == 2)
		printf("%ld %d is eating\n", get_time(pth), pth->name);
	else if (which == 3)
		printf("%ld %d is sleeping\n", get_time(pth), pth->name);
	else if (which == 4)
	{
		printf("%ld %d died\n", get_time(pth), pth->name);
		pth->info->end = ON;
	}
	else if (which == 5)
	{
		printf("%ld all enough\n", get_time(pth));
		pth->info->end = ON;
	}
}

int	prt_status(t_pth *pth, int which)
{
	pthread_mutex_lock(&(pth->info->mprt));
	pthread_mutex_lock(&(pth->info->mend));
	if (pth->info->end == ON)
	{
		pthread_mutex_unlock(&(pth->info->mend));
		pthread_mutex_unlock(&(pth->info->mprt));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(pth->info->mend));
	prt_status_msg(pth, which);
	pthread_mutex_unlock(&(pth->info->mprt));
	return (EXIT_SUCCESS);
}

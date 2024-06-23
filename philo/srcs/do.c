/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/23 17:49:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	_sleep(t_pth *pth)
{
	int	curtime;

	if (chk_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	curtime = get_time(pth);
	printf("%d %d is sleeping\n", curtime, pth->name);
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
	pthread_mutex_lock(&(pth->info->lock));
	if (pth->info->end == ON)
	{
		pthread_mutex_unlock(&(pth->info->lock));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(pth->info->lock));
	printf("%ld %d is thinking\n", get_time(pth), pth->name);
	pth->think = 1;
	return (EXIT_SUCCESS);
}

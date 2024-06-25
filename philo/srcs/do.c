/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 18:15:10 by jeshin           ###   ########.fr       */
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
	ft_printf(pth, 3);
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
	ft_printf(pth, 0);
	pth->think = 1;
	return (EXIT_SUCCESS);
}

void	ft_printf(t_pth *pth, int which)
{
	pthread_mutex_lock(&(pth->info->mprt));
	if (pth->info->end == ON)
	{
		pthread_mutex_unlock(&(pth->info->mprt));
		return ;
	}
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
	pthread_mutex_unlock(&(pth->info->mprt));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/13 18:03:33 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	_sleep(t_pth *pth)
{
	if (is_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	printf("%d %d is sleeping\n", get_time(pth), pth->name);
	usleep(pth->info->args->time_to_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	think(t_pth *pth)
{
	if (is_dead(pth) == TRUE)
		return (EXIT_FAILURE);
	printf("%d %d is thinking\n", get_time(pth), pth->name);
	return (EXIT_SUCCESS);
}

int	die(t_pth *pth)
{
	printf("%d %d died\n", get_time(pth), pth->name);
	pth->dead = ON;
	return (EXIT_SUCCESS);
}

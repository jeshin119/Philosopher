/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 17:57:18 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	_sleep(t_philo *p)
{
	int	curtime;

	curtime = get_time(p);
	printf("%d %d is sleeping\n", curtime, p->name);
	while (get_time(p) <= curtime + p->info->args->time_to_sleep)
	{
		usleep(100);
		chk_dead(p);
	}
	return (EXIT_SUCCESS);
}

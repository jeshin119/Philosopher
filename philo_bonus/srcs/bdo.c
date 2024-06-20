/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 12:41:33 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	_sleep(t_pth *pth)
{
	int	curtime;

	curtime = get_time(pth);
	printf("%d %d is sleeping\n", curtime, pth->name);
	while (get_time(pth) <= curtime + pth->info->args->time_to_sleep)
	{
		usleep(100);
		if (chk_dead(pth) == TRUE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

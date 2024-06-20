/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bchk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 17:56:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	chk_atecnt(t_philo *p)
{
	if (p->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (p->atecnt >= p->info->args->must_eat_times)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	chk_dead(t_philo *p)
{
	long	curtime;
	long	dietime;

	curtime = get_time(p);
	dietime = p->info->args->time_to_die;
	if (curtime - p->atetime >= dietime)
	{
		printf("%ld %d died\n", get_time(p), p->name);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 18:38:13 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	eat(t_philo *p)
{
	long	curtime;

	if (p->prvate)
		return (EXIT_FAILURE);
	if (sem_wait(p->info->sem))
		return (EXIT_FAILURE);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	curtime = get_time(p);
	printf("%ld %d is eating\n", curtime, p->name);
	while (get_time(p) <= curtime + p->info->args->time_to_eat)
	{
		chk_dead(p);
		usleep(100);
	}
	p->atetime = get_time(p);
	p->atecnt++;
	p->prvate = 1;
	sem_post(p->info->sem);
	return (EXIT_SUCCESS);
}

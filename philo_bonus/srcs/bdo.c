/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/24 13:05:02 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	chk_dead(t_philo *p)
{
	long	curtime;
	long	dietime;
	int		i;

	usleep(100);
	curtime = get_time(p);
	dietime = p->info->time_to_die;
	if (curtime - p->atetime >= dietime)
	{
		printf("%ld %d died\n", get_time(p), p->name);
		i = -1;
		while (++i < p->info->number)
		{
			if (p->info->ptab[i].pid == p->pid)
				continue ;
			kill(p->info->ptab[i].pid, SIGKILL);
		}
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	eat(t_philo *p)
{
	long	curtime;

	usleep(100);
	if (sem_wait(p->info->fork))
		return (EXIT_FAILURE);
	if (sem_wait(p->info->fork))
		return (EXIT_FAILURE);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	curtime = get_time(p);
	printf("%ld %d is eating\n", curtime, p->name);
	while (get_time(p) <= curtime + p->info->time_to_eat)
	{
		chk_dead(p);
		usleep(100);
	}
	p->atetime = get_time(p);
	p->atecnt++;
	sem_post(p->info->fork);
	sem_post(p->info->fork);
	return (EXIT_SUCCESS);
}

int	_sleep(t_philo *p)
{
	int	curtime;

	if (p->atecnt == p->info->must_eat_times)
	{
		sem_post(p->info->eatingend);
		return (EXIT_SUCCESS);
	}
	curtime = get_time(p);
	printf("%d %d is sleeping\n", curtime, p->name);
	while (get_time(p) <= curtime + p->info->time_to_sleep)
	{
		usleep(100);
		chk_dead(p);
	}
	return (EXIT_SUCCESS);
}

int	_think(t_philo *p)
{
	usleep(100);
	// chk_dead(p);
	printf("%ld %d is thinking\n", get_time(p), p->name);
	p->think = 1;
	return (EXIT_SUCCESS);
}

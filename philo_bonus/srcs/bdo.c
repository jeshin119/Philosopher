/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:47:23 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	chk_dead(t_philo *p)
{
	long	curtime;
	long	dietime;

	usleep(100);
	curtime = get_time(p);
	dietime = p->info->time_to_die;
	if (curtime - p->atetime >= dietime)
	{
		sem_wait(p->info->prt);
		printf("%ld %d died\n", get_time(p), p->name);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	hold_fork(t_philo *p)
{
	sem_wait(p->info->fork);
	sem_wait(p->info->prt);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	sem_post(p->info->prt);
	sem_wait(p->info->fork);
	sem_wait(p->info->prt);
	printf("%ld %d has taken a fork\n", get_time(p), p->name);
	sem_post(p->info->prt);
	return (EXIT_SUCCESS);
}

int	eat(t_philo *p)
{
	long	curtime;

	usleep(100);
	chk_dead(p);
	hold_fork(p);
	curtime = get_time(p);
	sem_wait(p->info->prt);
	printf("%ld %d is eating\n", curtime, p->name);
	sem_post(p->info->prt);
	while (get_time(p) <= curtime + p->info->time_to_eat)
	{
		usleep(100);
		chk_dead(p);
	}
	p->atetime = get_time(p);
	p->atecnt++;
	if (p->atecnt == p->info->must_eat_times)
	{
		sem_post(p->info->enough);
		usleep(100);
	}
	sem_post(p->info->fork);
	sem_post(p->info->fork);
	return (EXIT_SUCCESS);
}

int	_sleep(t_philo *p)
{
	int				curtime;

	usleep(100);
	chk_dead(p);
	curtime = get_time(p);
	sem_wait(p->info->prt);
	printf("%d %d is sleeping\n", curtime, p->name);
	sem_post(p->info->prt);
	while (get_time(p) <= curtime + p->info->time_to_sleep)
	{
		usleep(100);
		chk_dead(p);
	}
	p->think = 0;
	return (EXIT_SUCCESS);
}

int	_think(t_philo *p)
{
	usleep(100);
	chk_dead(p);
	if (p->think == 1)
		return (EXIT_FAILURE);
	sem_wait(p->info->prt);
	printf("%ld %d is thinking\n", get_time(p), p->name);
	sem_post(p->info->prt);
	p->think = 1;
	return (EXIT_SUCCESS);
}

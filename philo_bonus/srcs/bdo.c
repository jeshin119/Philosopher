/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/21 21:04:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

void	putmsgwithtime(char *msg, long time, int name)
{
	//printf 버퍼때문에 리다이렉션 안됨. write을 사용하면 바로 찍힘.
	write(1,)
}

int	chk_atecnt(t_philo *p)
{
	if (p->info->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (p->atecnt >= p->info->must_eat_times)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	chk_dead(t_philo *p)
{
	long	curtime;
	long	dietime;
	int		i;

	curtime = get_time(p);
	dietime = p->info->time_to_die;
	if (curtime - p->atetime >= dietime)
	{
		sem_post(p->info->whodead);
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

	curtime = get_time(p);
	printf("%d %d is sleeping\n", curtime, p->name);
	while (get_time(p) <= curtime + p->info->time_to_sleep)
	{
		usleep(100);
		chk_dead(p);
	}
	return (EXIT_SUCCESS);
}

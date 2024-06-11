/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:46:42 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	_sleep(t_pth *pth)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	printf("%ld %d is sleeping\n", \
	(t.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	usleep(pth->info->args->time_to_sleep * 1000);
	if (chk_died(pth) == TURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	think(t_pth *pth)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	printf("%ld %d is thinking\n", \
	(t.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	if (chk_died(pth) == TURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	die(t_pth *pth)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	printf("%ld %d died\n", \
	(t.tv_sec - pth->info->starttime.tv_sec) / 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) * 1000, pth->name);
	return (EXIT_SUCCESS);
}

int	chk_died(t_pth *pth)
{
	struct timeval	t;
	long int		cmp;

	gettimeofday(&t, NULL);
	cmp = (t.tv_sec - pth->atetime.tv_sec) + \
	(long int)(t.tv_usec - pth->atetime.tv_usec) * 1000;
	printf("cmp : %ld\n",cmp);
	printf("2 : %ld\n",(long int)pth->info->args->time_to_die);
	if (cmp > (long int)pth->info->args->time_to_die * 1000)
	{
		die(pth);
		return (TURE);
	}
	return (FALSE);
}

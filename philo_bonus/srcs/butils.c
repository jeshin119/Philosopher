/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:35:49 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:38:54 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[++i])
		;
	return (i);
}

void	handle_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	handle_one_philo_case(t_info *info)
{
	struct timeval	t;
	long			tt;

	gettimeofday(&t, NULL);
	tt = (t.tv_sec - info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - info->starttime.tv_usec) / 1000;
	printf("%ld %d is thinking\n", tt, 1);
	usleep(info->time_to_die * 1000);
	gettimeofday(&t, NULL);
	tt = (t.tv_sec - info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - info->starttime.tv_usec) / 1000;
	printf("%ld %d died\n", tt, 1);
}

int	closesem(t_info *info)
{
	if (sem_post(info->fork))
		handle_error("sem post: ");
	if (sem_close(info->fork))
		handle_error("sem close: ");
	if (sem_post(info->end))
		handle_error("sem post: ");
	if (sem_close(info->end))
		handle_error("sem close: ");
	if (sem_post(info->enough))
		handle_error("sem post: ");
	if (sem_close(info->enough))
		handle_error("sem close: ");
	if (sem_post(info->prt))
		handle_error("sem post: ");
	if (sem_close(info->prt))
		handle_error("sem close: ");
	if (sem_unlink("/fork"))
		handle_error("sem unlink: ");
	if (sem_unlink("/end"))
		handle_error("sem unlink: ");
	if (sem_unlink("/enough"))
		handle_error("sem unlink: ");
	if (sem_unlink("/prt"))
		handle_error("sem unlink: ");
	return (EXIT_SUCCESS);
}

long	get_time(t_philo *p)
{
	struct timeval	t;
	long			ret;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - p->info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - p->info->starttime.tv_usec) / 1000;
	return (ret);
}

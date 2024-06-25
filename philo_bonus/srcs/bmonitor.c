/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmonitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:29:26 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:36:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static void	put_enough(t_info *info)
{
	struct timeval	st;
	long			t;

	sem_wait(info->prt);
	gettimeofday(&st, NULL);
	t = (st.tv_sec - info->starttime.tv_sec) * 1000 + \
	(st.tv_usec - info->starttime.tv_usec) / 1000;
	printf("%ld all enough\n", t);
}

void	*chkenough(void *ags)
{
	t_info			*info;
	int				i;

	info = (t_info *)ags;
	while (TRUE)
	{
		sem_wait(info->enough);
		info->nenough++;
		if (info->nenough == info->number)
		{
			i = -1;
			while (++i < info->number)
				kill(info->ptab[i].pid, SIGKILL);
			put_enough(info);
			closesem(info);
			free(info->ptab);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	monitoring(t_info *info)
{
	pthread_t	chkenough_monitor;

	pthread_create(&(chkenough_monitor), 0, chkenough, (void *)info);
	pthread_detach(chkenough_monitor);
	return (EXIT_SUCCESS);
}

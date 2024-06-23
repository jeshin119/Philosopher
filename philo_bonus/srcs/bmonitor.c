/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmonitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:29:26 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/23 17:54:45 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

void	endphilos(t_info *info)
{
	if (sem_post(info->fork))
		handle_error("sem post: ");
	if (sem_close(info->fork))
		handle_error("sem close: ");
	if (sem_post(info->eatingend))
		handle_error("sem post: ");
	if (sem_close(info->eatingend))
		handle_error("sem close: ");
	if (sem_unlink("/fork"))
		handle_error("sem unlink: ");
	if (sem_unlink("/eatingend"))
		handle_error("sem unlink: ");
	free(info->ptab);
	exit(EXIT_SUCCESS);
}

void	*eatenough(void *ags)
{
	t_info	*info;
	int		i;

	info = (t_info *)ags;
	i = -1;
	while (info->status == 0)
	{
		usleep(100);
		sem_wait(info->eatingend);
		info->enough++;
		if (info->enough == info->number)
		{
			while (++i < info->number)
				kill(info->ptab[i].pid, SIGKILL);
			printf("all enough\n");
			endphilos(info);
		}
	}
	return (NULL);
}

void	waitphilos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number)
	{
		waitpid(-1, &info->status, 0);
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status != 0)
				endphilos(info);
		}
	}
}

int	monitoring(t_info *info)
{
	pthread_t	monitor_chkenough;

	pthread_create(&(monitor_chkenough), 0, eatenough, (void *)info);
	pthread_detach(monitor_chkenough);
	return (EXIT_SUCCESS);
}

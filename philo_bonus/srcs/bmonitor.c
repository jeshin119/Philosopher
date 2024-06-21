/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmonitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:29:26 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/21 20:46:40 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

void	endphilos(t_info *info)
{
	if (sem_post(info->fork))
		handle_error("sem close: ");
	if (sem_close(info->fork))
		handle_error("sem close: ");
	if (sem_close(info->eatingend))
		handle_error("sem close: ");
	if (sem_close(info->whodead))
		handle_error("sem close: ");
	if (sem_unlink("/fork"))
		handle_error("sem unlink: ");
	if (sem_unlink("/whodead"))
		handle_error("sem unlink: ");
	if (sem_unlink("/eatingend"))
		handle_error("sem unlink: ");
	free(info->ptab);
	exit(EXIT_SUCCESS);
}

void	*whodead(void *ags)
{
	t_info	*info;

	info = (t_info *)ags;
	sem_wait(info->whodead);
	endphilos(info);
	return (NULL);
}

void	*eatenough(void *ags)
{
	t_info	*info;

	info = (t_info *)ags;
	while (info->status == 0)
	{
		sem_wait(info->eatingend);
		info->enough++;
		if (info->enough == info->number)
			endphilos(info);
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
			info->status = WEXITSTATUS(info->status);
	}
}

int	monitoring(t_info *info)
{
	pthread_t	monitor_chkdead;
	pthread_t	monitor_chkenough;

	pthread_create(&(monitor_chkdead), 0, whodead, (void *)info);
	pthread_detach(monitor_chkdead);
	pthread_create(&(monitor_chkenough), 0, eatenough, (void *)info);
	pthread_detach(monitor_chkenough);
	return (EXIT_SUCCESS);
}

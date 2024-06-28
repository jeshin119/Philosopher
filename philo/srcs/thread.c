/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/28 15:21:33 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	join_pthreads(t_info *info)
{
	pthread_t	id;
	int			i;

	i = -1;
	while (++i < info->args->number)
	{
		id = ((info->pth_tab)[i]).pth_id;
		if (pthread_join(id, NULL))
			return (handle_error("pthread join"));
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

static void	*start_routine(void *ags)
{
	t_pth		*pth;
	int			left;
	int			right;
	int			status;

	pth = (t_pth *)ags;
	set_left_right(&left, &right, pth);
	while (TRUE)
	{
		if (think(pth) == EXIT_FAILURE)
			return (NULL);
		status = eat(left, right, pth);
		if (status == EXIT_FAILURE)
			continue ;
		if (status == END)
			return (NULL);
		if (_sleep(pth) == EXIT_FAILURE)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	start(t_info *info)
{
	t_pth	*pth;
	int		i;

	if (info->args->number == 1)
	{
		handle_one_philo_case(info);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < info->args->number)
	{
		pth = &((info->pth_tab)[i]);
		pth->name = i + 1;
		pth->info = info;
		if (pthread_create(&(pth->pth_id), 0, start_routine, (void *)(pth)))
			return (handle_error("pthread_create"));
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

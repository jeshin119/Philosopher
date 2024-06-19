/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/19 22:06:01 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	monitoring(t_info *info)
{
	int	i;
	int	prev;

	while (TRUE)
	{
		i = -1;
		while (++i < info->args->number)
		{
			if (info->args->must_eat_times != -1 && \
			info->enough >= info->args->number)
			{
				info->end = ON;
				return ;
			}
			if ((info->pth_tab)[i].dead)
			{
				info->end = ON;
				return ;
			}
			usleep(100);
		}
	}
}

void	join_pthreads(t_info *info)
{
	void		*status;
	pthread_t	id;
	int			i;

	i = -1;
	while (++i < info->args->number)
	{
		id = ((info->pth_tab)[i]).pth_id;
		if (pthread_join(id, &status))
			handle_error("pthread join");
	}
}

static void	*start_routine(void *ags)
{
	t_pth		*pth;
	int			think;

	pth = (t_pth *)ags;
	think = 0;
	while (TRUE)
	{
		if (chk_dead(pth) == TRUE)
			return (NULL);
		if (chk_atecnt(pth))
			return (NULL);
		if (try_eat(pth) == EXIT_SUCCESS)
		{
			if (pth->dead == ON)
				return (NULL);
			_sleep(pth);
			think = 0;
		}
		if (think == 0)
		{
			printf("%ld %d is thinking\n", get_time(pth), pth->name);
			think = 1;
		}
		usleep(100);
	}
}

int	start(t_info *info)
{
	t_pth	*pth;
	int		i;

	if (info->args->number == 1)
	{
		handle_one_philo_case(info);
		return (EXIT_SUCCESS);
	}
	i = -1;
	while (++i < info->args->number)
	{
		pth = &((info->pth_tab)[i]);
		pth->name = i + 1;
		pth->info = info;
		if (pthread_create(&(pth->pth_id), 0, start_routine, (void *)(pth)))
			handle_error("pthread_create");
		usleep(100);
	}
	monitoring(info);
	join_pthreads(info);
	return (EXIT_SUCCESS);
}

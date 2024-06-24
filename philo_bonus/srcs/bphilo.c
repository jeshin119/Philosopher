/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/24 11:31:02 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static int	eacheating(t_philo *p)
{
	while (TRUE)
	{
		chk_dead(p);
		if (p->think == 0)
		{
			usleep(100);
			_think(p);
			p->think = 1;
		}
		usleep(100);
		if (eat(p) == EXIT_SUCCESS)
		{
			usleep(100);
			_sleep(p);
			p->think = 0;
		}
	}
	exit(EXIT_SUCCESS);
}

int	start(t_info *info)
{
	int		i;
	t_philo	*p;

	if (info->number == 1)
	{
		handle_one_philo_case(info);
		return (EXIT_SUCCESS);
	}
	i = -1;
	while (++i < info->number)
	{
		p = &(info->ptab[i]);
		p->pid = fork();
		if (p->pid < 0)
			handle_error("fork: ");
		if (p->pid != 0)
			continue ;
		p->name = i + 1;
		p->info = info;
		eacheating(p);
	}
	return (EXIT_SUCCESS);
}

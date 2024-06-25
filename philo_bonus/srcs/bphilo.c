/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:46:11 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static int	starteating(t_philo *p)
{
	while (TRUE)
	{
		_think(p);
		if (eat(p) == EXIT_SUCCESS)
			_sleep(p);
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
		starteating(p);
	}
	return (EXIT_SUCCESS);
}

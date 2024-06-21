/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/21 20:23:10 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static int	eacheating(t_philo *p)
{
	while (TRUE)
	{
		chk_dead(p);
		chk_atecnt(p);
		if (p->think == 0)
		{
			chk_dead(p);
			printf("%ld %d is thinking\n", get_time(p), p->name);
			p->think = 1;
		}
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
	monitoring(info);
	waitphilos(info);
	return (EXIT_SUCCESS);
}

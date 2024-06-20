/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:05:59 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 20:24:20 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static int	eacheating(t_philo *p)
{
	while (TRUE)
	{
		chk_dead(p);
		chk_atecnt(p);
		if (eat(p) == EXIT_SUCCESS)
		{
			_sleep(p);
			p->think = 0;
		}
		if (p->think == 0)
		{
			printf("%ld %d is thinking\n", get_time(p), p->name);
			p->think = 1;
			p->prvate = 0;
		}
	}
	exit(EXIT_FAILURE);
}

int	start(t_info *info)
{
	int		i;
	t_philo *ph;

	if (info->number == 1)
	{
		handle_one_philo_case(info);
		return (EXIT_SUCCESS);
	}
	i = -1;
	while (++i < info->args->number)
	{
		ph = &((info->philo_tab)[i]);
		ph->name = i + 1;
		ph->info = info;
		ph->pid = fork();
		if (ph->pid == 0)
			continue ;
		else if (ph->pid < 0)
			handle_error("fork: ");
		eacheating(ph);
	}
	return (EXIT_SUCCESS);
}

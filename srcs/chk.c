/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 17:27:36 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	chk_musteat_times(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (pth->ate_times >= pth->info->args->must_eat_times)
	{
		pth->info->enough++;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	chk_equal(t_pth *pth, int left, int right)
{
	if (pth->info->fork_tab[left].is_locked == ON | pth->info->fork_tab[right].is_locked == ON)
		return (EXIT_FAILURE);
	if ((pth->info->fork_tab)[left].who_ate == pth->name && (pth->info->fork_tab)[right].who_ate == pth->name)
		return (EXIT_FAILURE);
	// if (get_atetime(pth) > pth->info->starving)
		// return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	chk_dead(t_pth *pth)
{
	int	curtime;
	int	atetime;
	int	dietime;

	curtime = get_time(pth);
	atetime = get_atetime(pth);
	dietime = pth->info->args->time_to_die;
	if (curtime - atetime >= dietime)
	{
		printf("%d %d died\n", get_time(pth), pth->name);
		pth->dead = ON;
		return (TRUE);
	}
	return (FALSE);
}

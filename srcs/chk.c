/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/12 18:27:39 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	chk_musteat_times(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (pth->ate_times >= pth->info->args->must_eat_times)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	chk_left_right(int *left, int *right, t_pth *pth)
{
	*left = pth->name - 1;
	if (pth->name == pth->info->args->number + 1)
		*right = 0;
	else
		*right = pth->name;
	if (pth->info->fork_tab[*left] || pth->info->fork_tab[*right])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	chk_equal(t_pth *pth)
{
	return (EXIT_SUCCESS);
}

int	chk_died(t_pth *pth)
{
	int	curtime;
	int	atetime;

	curtime = get_time(pth);
	atetime = get_atetime(pth);
	if (curtime - atetime > pth->info->args->time_to_die * 1000)
	{
		die(pth);
		return (TURE);
	}
	return (FALSE);
}

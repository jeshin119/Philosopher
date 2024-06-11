/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:33:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:27:46 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*start_routine(void *ags)
{
	t_pth		*pth;

	pth = (t_pth *)ags;
	while (chk_died(pth) == FALSE)
	{
		if (try_eat(pth))
			;
		if (think(pth))
			;
		if (_sleep(pth))
			;
	}
	return (0);
}

void	start(t_info *info)
{
	t_pth	*pth;
	int		i;

	i = -1;
	while (++i < info->args->number)
	{
		pth = &((info->pth_tab)[i]);
		pth->name = i + 1;
		pth->info = info;
		if (pthread_create(&(pth->pth_id), 0, start_routine, (void *)(pth)))
			handle_error("pthread_create");
	}
}

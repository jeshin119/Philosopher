/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/19 21:43:23 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_info(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->args->number)
	{
		if (pthread_mutex_destroy(&(info->mutex_tab[i])))
			handle_error("mutex destroy: ");
	}
	free(info->mutex_tab);
	free(info->fork_tab);
	free(info->pth_tab);
}

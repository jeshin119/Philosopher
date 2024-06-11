/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 16:51:40 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/10 18:01:05 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_pthreads(t_pth_info *pth_info, int cnt)
{
	int		pth_status;
	int		i;

	i = -1;
	while (++i < cnt)
	{
		pthread_join(pth_info->pth_id, (void*)&pth_status);
		if (pth_status != 0)
			handle_error_en(pth_status, "pthread");
	}
}
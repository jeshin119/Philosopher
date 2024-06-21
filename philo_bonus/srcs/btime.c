/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:14:13 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/21 19:26:22 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

long	get_time(t_philo *ph)
{
	struct timeval	t;
	long			ret;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - ph->info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - ph->info->starttime.tv_usec) / 1000;
	return (ret);
}

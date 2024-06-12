/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:14:13 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/12 18:24:44 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time(t_pth *pth)
{
	struct timeval	t;
	int				ret;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - pth->info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) / 1000;
	return (ret);
}

int	get_atetime(t_pth *pth)
{
	int				ret;

	ret = (pth->atetime.tv_sec - pth->info->starttime.tv_sec) * 1000 + \
	(pth->atetime.tv_usec - pth->info->starttime.tv_usec) / 1000;
	return (ret);
}

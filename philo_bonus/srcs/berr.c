/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 20:23:42 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

void	handle_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	handle_one_philo_case(t_info *info)
{
	struct timeval	t;
	long			ret;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - info->starttime.tv_usec) / 1000;
	printf("%ld %d is thinking\n", ret, 1);
	usleep(info->time_to_die * 1000);
	gettimeofday(&t, NULL);
	ret = (t.tv_sec - info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - info->starttime.tv_usec) / 1000;
	printf("%ld %d died\n", ret, 1);
}

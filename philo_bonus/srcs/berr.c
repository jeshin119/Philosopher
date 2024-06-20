/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 15:59:44 by jeshin           ###   ########.fr       */
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
	t_philo	*ph;

	ph = &((info->philo_tab)[0]);
	ph->name = 1;
	ph->info = info;
	printf("%ld %d is thinking\n", get_time(ph), ph->name);
	usleep(info->args->time_to_die * 1000);
	printf("%ld %d died\n", get_time(ph), ph->name);
}

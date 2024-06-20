/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 11:50:28 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	handle_error(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

void	handle_one_philo_case(t_info *info)
{
	t_pth	*pth;

	pth = &((info->pth_tab)[0]);
	pth->name = 1;
	pth->info = info;
	printf("%ld %d is thinking\n", get_time(pth), pth->name);
	usleep(info->args->time_to_die * 1000);
	printf("%ld %d died\n", get_time(pth), pth->name);
}

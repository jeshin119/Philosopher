/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/24 17:06:11 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[++i])
		;
	return (i);
}

int	handle_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
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

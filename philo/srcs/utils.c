/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 18:26:17 by jeshin           ###   ########.fr       */
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

int	free_info(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->args->number)
	{
		if (pthread_mutex_destroy(&(info->mutex_tab[i])))
			return (handle_error("mutex destroy: "));
	}
	if (pthread_mutex_destroy(&(info->mprt)))
		return (handle_error("mutex destroy: "));
	if (pthread_mutex_destroy(&(info->mend)))
		return (handle_error("mutex destroy: "));
	free(info->mutex_tab);
	free(info->fork_tab);
	free(info->pth_tab);
	return (EXIT_SUCCESS);
}

long	get_time(t_pth *pth)
{
	struct timeval	t;
	long			ret;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - pth->info->starttime.tv_sec) * 1000 + \
	(t.tv_usec - pth->info->starttime.tv_usec) / 1000;
	return (ret);
}

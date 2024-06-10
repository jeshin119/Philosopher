/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:20 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/10 18:02:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_argumnets(int ac, char **av, t_arg_info *arg_info)
{
	if (ac < 4 || ac > 5)
		exit(EXIT_FAILURE);
	arg_info->number = ft_atoi(av[1]);
	if (arg_info->number < 0)
		exit(EXIT_FAILURE);
	arg_info->time_to_die = ft_atoi(av[2]);
	if (arg_info->time_to_die < 0)
		exit(EXIT_FAILURE);
	arg_info->time_to_eat = ft_atoi(av[3]);
	if (arg_info->time_to_eat < 0)
		exit(EXIT_FAILURE);
	arg_info->time_to_sleep = ft_atoi(av[4]);
	if (arg_info->time_to_sleep < 0)
		exit(EXIT_FAILURE);
	if (av[5] != NULL)
	{
		arg_info->must_eat_times = ft_atoi(av[5]);
		if (arg_info->must_eat_times < 0)
			exit(EXIT_FAILURE);
	}
}

void	init_fork_tab(int **fork_tab, int size)
{
	*fork_tab = (int *)malloc(sizeof(int) * size);
	if (*fork_tab == 0)
		handle_error("malloc fork tab");
	memset(*fork_tab, 0, sizeof(int) * size);
}

static void	*start_routine(void *arg)
{
	printf("hi %p\n",arg);
	return (arg);
}

void	init_philos(t_pth_info **pth_info, int number_of_philos)
{
	int	i;

	*pth_info = (t_pth_info *)malloc(sizeof(t_pth_info) * number_of_philos);
	if (*pth_info == 0)
		handle_error("malloc pth_info");
	memset(*pth_info, 0, sizeof(t_pth_info) * number_of_philos);
	i=-1;
	while (++i < number_of_philos)
	{
		((*pth_info)[i]).pth_num = pthread_create(&(((*pth_info)[i]).pth_id), 0, start_routine, 0);
		if (((*pth_info)[i]).pth_id == 0)
			handle_error_en(((*pth_info)[i]).pth_num, "pthread_create");
	}
}
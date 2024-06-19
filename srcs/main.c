/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:56 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 16:22:27 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_info(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->args->number)
	{
		if (pthread_mutex_destroy(&(info->mutex_tab[i])))
			handle_error("mutex destroy: ");
	}
	free(info->mutex_tab);
	free(info->fork_tab);
	free(info->pth_tab);
}

int	who_startved(t_info *info)
{
	int	i;
	int min;

	i = -1;
	min = 2147483647;
	while (++i < info->args->number)
	{
		if (min >= get_atetime(&(info->pth_tab[i])))
			min = get_atetime(&(info->pth_tab[i]));
	}
	info->starving = min;
	return (EXIT_SUCCESS);
}

void	monitoring(t_info *info)
{
	int	i;

	while (TRUE)
	{
		i = -1;
		while (++i < info->args->number)
		{
			if (info->args->must_eat_times != -1 && info->enough >= info->args->number)
				exit(EXIT_SUCCESS);
			if ((info->pth_tab)[i].dead)
				exit(EXIT_SUCCESS);
			who_startved(info);
			usleep(100);
		}
	}
}

//visualize제댈 되는건지? 다같이 자는 구간이 있음 .. 그래서 3 100 20 20 을 하면 계속 먹고 자고 생각해야하는데 누군가는 죽음.
//와일문에서 usleep을 넣어줘야하는지? 이런 찌라시를 봤는데 왜 그래야하는지?
//usleep을 왜쪼개서 쉬어야하는지? 먹는시간이 5초라면 5초가될때까지 작은 usleep을 반복하라는데, 왜그래야?
//usleep이 실행되서 thread가 sleep상테인 후에 깨어난다고 하면 스레드는 바로 run되지 않고 wait될 수도 있다. 이게 무슨 상관?
//왜 다같이 쉬는파트가 생기는건지? 5명일때?

//동ㅇ시에 자는 문제.
//죽을위기에 처한애가 못먹는게 문제.
int	main(int ac, char **av)
{
	t_info			info;
	t_args			args;

	init_argumnets(ac, av, &args);
	init_info(&args, &info);
	start(&info);
	monitoring(&info);
	join_pthreads(&info);
	free_info(&info);
	return (EXIT_SUCCESS);
}

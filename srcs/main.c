/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:56 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/13 18:37:05 by jeshin           ###   ########.fr       */
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

int	monitoring(t_info *info)
{
	int	i;

	while (TRUE)
	{
		i = -1;
		while (++i < info->args->number)
		{
			if ((info->pth_tab)[i].dead)
				exit(EXIT_SUCCESS);
			// usleep(20);
		}
			// usleep(20);
	}
}

//visualize제댈 되는건지?
//와일문에서 usleep을 넣어줘야하는지?
//usleep을 왜쪼개서 쉬어야하는지?
//왜 다같이 쉬는파트가 생기는건지? 5명일때?
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:56 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 18:23:51 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_info			info;
	t_args			args;

	if (init_info(ac, av, &args, &info))
		return (EXIT_FAILURE);
	if (start(&info))
	{
		free_info(&info);
		return (EXIT_SUCCESS);
	}
	if (join_pthreads(&info))
	{
		free_info(&info);
		return (EXIT_FAILURE);
	}
	if (free_info(&info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

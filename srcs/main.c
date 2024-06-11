/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:56 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:10:26 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_info			info;
	t_args			args;

	init_argumnets(ac, av, &args);
	init_info(&args, &info);
	start(&info);
	join_pthreads(&info);
	return (EXIT_SUCCESS);
}

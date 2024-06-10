/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:23:16 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/10 18:05:20 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	eat(t_pth_info pinfo, ){

// }

// void	think(){

// }
// void	die(){

// }

// void	zz(t_arg_info *lim, t_pth_info *pinfo, int *ftab){
// 	while(1){
// 		if (lim->)
// 	}
// }
int	main(int ac, char **av)
{
	t_arg_info	arg_info;
	t_pth_info	*pth_info;
	int			*fork_tab;
	pthread_mutex_t mutex;

	init_argumnets(ac, av, &arg_info);
	init_philos(&pth_info, arg_info.number);
	init_fork_tab(&fork_tab, arg_info.number);
	pthread_mutex_init(&mutex, 0);
	// zz(&arg_info, &pth_info, fork_tab);
	join_pthreads(pth_info, arg_info.number);
	printf("end\n");
}
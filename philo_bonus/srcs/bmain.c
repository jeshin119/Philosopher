/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:56 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 20:20:10 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	main(int ac, char **av)
{
	t_info			info;

	if (init_info(ac, av, &info))
		return (EXIT_FAILURE);
	start(&info);
	free_info(&info);
	return (EXIT_SUCCESS);
}

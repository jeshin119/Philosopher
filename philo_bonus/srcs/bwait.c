/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:36:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:37:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	waitphilos(t_info *info)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < info->number)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			i = -1;
			while (++i < info->number)
				kill(info->ptab[i].pid, SIGKILL);
			closesem(info);
			free(info->ptab);
			return (EXIT_SUCCESS);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

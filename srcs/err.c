/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:00:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/10 18:02:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	handle_error_en(int en,char *msg)
{
	errno = en;
	perror(msg);
	exit(EXIT_FAILURE);
}

void	handle_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
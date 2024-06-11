/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:05 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/11 18:10:43 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FALSE 1
# define TURE 0

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_args
{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
}	t_args;

typedef struct s_pth	t_pth;

typedef struct s_info
{
	t_args			*args;
	int				*fork_tab;
	pthread_mutex_t	*mutex_tab;
	t_pth			*pth_tab;
	struct timeval	starttime;
}	t_info;

typedef struct s_pth
{
	pthread_t		pth_id;
	int				name;
	int				ate_times;
	t_info			*info;
	struct timeval	atetime;
}	t_pth;

//ft_atoi.c
int		ft_atoi(const char *str);
//err.c
void	handle_error(char *msg);
//init.c
void	init_argumnets(int ac, char **av, t_args *args);
void	init_info(t_args *args, t_info *pinfo);
//free.c
void	join_pthreads(t_info *pinfo);
//eat.c
int		try_eat(t_pth *pth);
//thread.c
void	start(t_info *info);
//die.c
int		chk_died(t_pth *pth);
//do.c
int		think(t_pth *pth);
int		_sleep(t_pth *pth);
#endif
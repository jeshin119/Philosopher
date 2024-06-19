/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:05 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/14 16:21:26 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FALSE 0
# define TRUE 1
# define OFF 0
# define ON 1
# define DEAD 1
# define FINE 0


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

typedef struct s_fork
{
	int	is_locked;
	int	who_ate;
}	t_fork;

typedef struct s_pth	t_pth;

typedef struct s_info
{
	t_args			*args;
	t_fork			*fork_tab;
	pthread_mutex_t	*mutex_tab;
	t_pth			*pth_tab;
	struct timeval	starttime;
	int				starving;
	int				enough;
}	t_info;

struct s_pth
{
	pthread_t		pth_id;
	int				name;
	int				ate_times;
	int				dead;
	t_info			*info;
	struct timeval	atetime;
};

//ft_atoi.c
int		ft_atoi(const char *str);
//err.c
void	handle_error_en(int en, char *msg);
void	handle_error(char *msg);
//init.c
void	init_argumnets(int ac, char **av, t_args *args);
//init_info.c
void	init_info(t_args *args, t_info *pinfo);
//free.c
void	join_pthreads(t_info *pinfo);
//eat.c
int		try_eat(t_pth *pth);
//thread.c
void	start(t_info *info);
//do.c
int		_sleep(t_pth *pth);
//time.c
int		get_time(t_pth *pth);
int		get_atetime(t_pth *pth);
//chk.c
int		chk_musteat_times(t_pth *pth);
int		chk_equal(t_pth *pth, int left, int right);
int		chk_dead(t_pth *pth);
#endif
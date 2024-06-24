/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/24 18:28:03 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FALSE 0
# define TRUE 1
# define OFF 0
# define ON 1
# define END -1

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
	pthread_mutex_t	mend;
	pthread_mutex_t	mprt;
	t_pth			*pth_tab;
	struct timeval	starttime;
	int				enough;
	int				end;
}	t_info;

struct s_pth
{
	pthread_t		pth_id;
	int				name;
	int				atecnt;
	int				think;
	t_info			*info;
	long			atetime;
};

//ft_atoi.c
int		ft_atoi(const char *str);
//err.c
int		handle_error(char *msg);
void	handle_one_philo_case(t_info *info);
//init.c
int		init_info(int ac, char **av, t_args *args, t_info *pinfo);
//free.c
void	free_info(t_info *info);
//eat.c
int		eat(int left, int right, t_pth *pth);
int		set_left_right(int *left, int *right, t_pth *pth);
//thread.c
int		start(t_info *info);
int		join_pthreads(t_info *info);
//do.c
int		_sleep(t_pth *pth);
int		think(t_pth *pth);
int		ft_printf(t_pth *pth, int which);
//time.c
long	get_time(t_pth *pth);
//chk.c
int		chk_eat(t_pth *pth, int left, int right);
int		chk_atecnt(t_pth *pth);
int		chk_dead(t_pth *pth);
int		chk_enough(t_pth *pth);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:39:59 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BPHILO_H
# define BPHILO_H

# define FALSE 0
# define TRUE 1
# define OFF 0
# define ON 1

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	int				number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	sem_t			*fork;
	sem_t			*end;
	sem_t			*enough;
	sem_t			*prt;
	t_philo			*ptab;
	int				nenough;
	struct timeval	starttime;
}	t_info;

typedef struct s_philo
{
	pid_t			pid;
	t_info			*info;
	int				name;
	int				atecnt;
	int				think;
	long			atetime;
}	t_philo;

//bft_atoi.c
int		ft_atoi(const char *str);
//binit.c
int		init_info(int ac, char **av, t_info *pinfo);
//bphilo.c
int		start(t_info *info);
//bdo.c
int		chk_dead(t_philo *p);
int		eat(t_philo *p);
int		_sleep(t_philo *p);
int		_think(t_philo *p);
//butils.c
long	get_time(t_philo *p);
void	handle_error(char *msg);
void	handle_one_philo_case(t_info *info);
//bwait.c
int		waitphilos(t_info *info);
//bmonitor.c
int		monitoring(t_info *info);
int		closesem(t_info *info);
#endif
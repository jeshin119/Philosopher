/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 20:14:19 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FALSE 0
# define TRUE 1
# define OFF 0
# define ON 1

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_info
{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
	sem_t			fork;
	sem_t			endeating;
	sem_t			whodead;
	int				enough;
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

//ft_atoi.c
int		ft_atoi(const char *str);
//err.c
void	handle_error(char *msg);
void	handle_one_philo_case(t_info *info);
//binit.c
int		init_info(int ac, char **av, t_info *pinfo);
//free.c
void	free_info(t_info *info);
//beat.c
int		eat(t_philo *p);
//bphilo.c
int		start(t_info *info);
//do.c
int	_sleep(t_philo *p);
//time.c
long	get_time(t_philo *p);
//chk.c
int		chk_atecnt(t_philo *p);
int		chk_dead(t_philo *p);
#endif
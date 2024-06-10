#ifndef PHILO_H
#define PHILO_H

 #include <unistd.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <errno.h>
 #include <signal.h>


typedef struct s_arg_info
{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
}	t_arg_info;

typedef struct s_pth_info
{
	pthread_t	pth_id;
	int			pth_num;
	int			ate_times;
}	t_pth_info;

int	ft_atoi(const char *str);
//err.c
void	handle_error(char *msg);
void	handle_error_en(int en,char *msg);
//init.c
void	init_argumnets(int ac, char **av, t_arg_info *arg_info);
void	init_fork_tab(int **fork_tab, int size);
void	init_philos(t_pth_info **pth_info, int number_of_philos);
//free.c
void	join_pthreads(t_pth_info *pth_info, int cnt);
#endif
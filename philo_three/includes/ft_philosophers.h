/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:30:31 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/05 11:46:07 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include "philo_errors.h"
# include "messages.h"
# include "semaphores.h"
# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct				s_philosopher
{
	long int				dead_limit;
	int						eat_num;
	char					*num;
	char					*lock_name;
	char					*full_name;
	int						alive;
	int						stop;
	int						next_step;
	int						shift;

	struct s_philosopher	*next;

	sem_t					*lock;
	sem_t					*full;

	pid_t					process;
}							t_philosopher;

int							ft_strlen(char const *s);
char						*ft_strjoin(char const *s1, char const *s2,
										int fre);
char						*ft_itoa(int n);
int							ft_atoi(const char *str);
void						philo_life(t_philosopher *philo);
void						rspleep(t_philosopher *philo, long int time);
void						reat(t_philosopher *philo, long int time);
void						free_all(t_philosopher **phi);
int							init_threads(t_philosopher **philos);
t_philosopher				*init_phis(char **av, int ac);
long int					get_time();
long int					get_time_rel();
void						display_msg(t_philosopher *philo, int time,
								char *msg);
sem_t						*ft_sem_open(char const *name, int value);
char						*make_name(char const *base, int position);
void						*monitor_eat(void *philo_cpy);
void						*monitor_death(void *philo_cpy);
void						*monitor_stop(void *philo_cpy);

int							g_time_to_die;
int							g_time_to_sleep;
int							g_time_to_eat;
int							g_eat_num;
int							g_error;
int							g_phi_number;
sem_t						*g_stop;
long int					g_time_start;
sem_t						*g_forks;
sem_t						*g_write;

#endif

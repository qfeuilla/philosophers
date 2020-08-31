/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:30:31 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/29 21:43:00 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHER_H
# define FT_PHILOSOPHER_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "philo_errors.h"
# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct				s_philosopher
{
	int						time_to_die;
	int						eat_num;
	char 					*num;
	int						alive;
	int						actual_action;
	int						next_step;
	int						mutex_is_lock;

	pthread_t				thread;
	pthread_mutex_t			mutex;

	struct s_philosopher	*next;
	struct s_philosopher	*prev;

}							t_philosopher;

int							ft_strlen(char const *s);
char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_itoa(int n);
int							ft_atoi(const char *str);
void 						*philo_life(void *philo_cpy);
void						rspleep(t_philosopher *philo);
void						rthink(t_philosopher *philo);
void						reat(t_philosopher *philo);
void						rdeath(t_philosopher *philo);
void						free_all(t_philosopher **phi);
int							init_threads(t_philosopher **philos);

int							g_time_to_die;
int							g_time_to_sleep;
int							g_time_to_eat;
int							g_time_stamp;
int							g_error;
int							g_phi_number;
int							g_start;
int							g_stop;

#endif
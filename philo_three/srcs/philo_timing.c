/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:13:55 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/02 17:34:27 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void						put_die(t_philosopher *philo)
{
	char			*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(g_tmp_st->__align), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " died\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
}

void						*chronos(void *philo_cpy)
{
	t_philosopher	*philo;
	long int		old;

	philo = (t_philosopher *)philo_cpy;
	while (1)
		if (g_start->__align)
			break ;
	old = 0;
	while (!g_stop->__align)
		if (old != (long int)g_tmp_st->__align && (long int)g_tmp_st->__align)
		{
			philo->time_to_die -= g_tmp_st->__align - old;
			if (philo->alive == 0)
			{
				if (philo->eat_num != 0)
					put_die(philo);
				sem_post(g_stop);
				break ;
			}
			old = g_tmp_st->__align;
		}
	return (philo);
}

void						init_life(pthread_t *ch, t_philosopher *philo)
{
	g_start = sem_open(SEM_START, 0);
	g_tmp_st = sem_open(SEM_TIMESTAMP, 0);
	g_stop = sem_open(SEM_STOP, 0);
	g_philo_full = sem_open(SEM_FULL, 0);
	g_philo_turn = sem_open(SEM_TURN, 0);
	pthread_create(ch, NULL, chronos, philo);
}

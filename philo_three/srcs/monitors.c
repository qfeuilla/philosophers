/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 11:29:24 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/05 11:43:23 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void				*monitor_eat(void *philo_cpy)
{
	t_philosopher	*tmp;
	int				already;

	tmp = philo_cpy;
	already = 0;
	while (!already || (ft_atoi(tmp->num) != 1))
	{
		sem_wait(tmp->full);
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		tmp = tmp->next;
	}
	sem_post(g_stop);
	return ((void *)0);
}

void				*monitor_death(void *philo_cpy)
{
	t_philosopher	*philo;
	long int		tmp;

	philo = (t_philosopher *)philo_cpy;
	while (!philo->stop)
	{
		sem_wait(philo->lock);
		if (((tmp = get_time_rel())) > philo->dead_limit)
		{
			display_msg(philo, tmp, MS_DEAD);
			sem_post(philo->lock);
			sem_post(g_stop);
			return ((void*)0);
		}
		sem_post(philo->lock);
		usleep(100);
	}
	return ((void *)0);
}

void				*monitor_stop(void *philo_cpy)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_cpy;
	sem_wait(g_stop);
	sem_post(g_stop);
	philo->stop = 1;
	return ((void *)0);
}

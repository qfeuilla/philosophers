/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 17:03:36 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/05 11:27:21 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void		rspleep(t_philosopher *philo, long int time)
{
	sem_post(g_forks);
	sem_post(g_forks);
	if (philo->eat_num == 0)
	{
		philo->eat_num--;
		sem_post(philo->full);
	}
	display_msg(philo, get_time_rel(), MS_SLEEP);
	philo->shift = time - philo->next_step;
	philo->next_step = time + g_time_to_sleep;
	usleep((long)g_time_to_sleep * 1000 - ((get_time_rel() - time)
		+ philo->shift) * 1000);
}

void		reat(t_philosopher *philo, long int time)
{
	sem_wait(philo->lock);
	time = get_time_rel();
	philo->dead_limit = time + g_time_to_die;
	philo->next_step = time + g_time_to_eat;
	display_msg(philo, time, MS_EAT);
	usleep((long)g_time_to_eat * 1000 - ((get_time_rel() - time)) * 1000);
	philo->eat_num--;
	sem_post(philo->lock);
}

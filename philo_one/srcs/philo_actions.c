/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 17:03:36 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 17:09:13 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void		rspleep(t_philosopher *philo, long int time)
{
	pthread_mutex_unlock(&(g_forks[philo->fork_l]));
	pthread_mutex_unlock(&(g_forks[philo->fork_r]));
	if (philo->eat_num == 0)
	{
		philo->eat_num--;
		g_philo_full++;
	}
	display_msg(philo, get_time_rel(), MS_SLEEP);
	usleep((long)g_time_to_sleep * 1000 - ((get_time_rel() - time) + 10));
}

void		reat(t_philosopher *philo, long int time)
{
	pthread_mutex_lock(&philo->mutex);
	time = get_time_rel();
	philo->dead_limit = time + g_time_to_die;
	display_msg(philo, time, MS_EAT);
	usleep((long)g_time_to_eat * 1000 - ((get_time_rel() - time) + 10));
	philo->eat_num--;
	pthread_mutex_unlock(&philo->mutex);
}

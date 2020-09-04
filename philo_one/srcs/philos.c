/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 19:47:00 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void				*monitor_death(void *philo_cpy)
{
	t_philosopher	*philo;
	long int		tmp;

	philo = (t_philosopher *)philo_cpy;
	while (!g_stop)
	{
		pthread_mutex_lock(&philo->mutex);
		if (((tmp = get_time_rel())) > philo->dead_limit)
		{
			display_msg(philo, tmp, MS_DEAD);
			pthread_mutex_unlock(&philo->mutex);
			g_stop = 1;
			return ((void*)0);
		}
		if (g_philo_full == g_phi_number)
			g_stop = 1;
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
	return ((void *)0);
}

void				*philo_life(void *philo_cpy)
{
	pthread_t		monitor;
	t_philosopher	*philo;

	philo = philo_cpy;
	if (pthread_create(&monitor, NULL, monitor_death, philo_cpy) != 0)
		return ((void*)1);
	pthread_detach(monitor);
	usleep(ft_atoi(philo->num) * 100);
	while (!g_stop)
	{
		if (!g_stop)
			take_forks(philo);
		if (!g_stop)
			reat(philo, get_time_rel());
		if (!g_stop)
			rspleep(philo, get_time_rel());
		if (!g_stop)
			display_msg(philo, get_time_rel(), MS_THINK);
	}
	return (philo_cpy);
}

void				*close_globals(void)
{
	pthread_mutex_lock(&g_write);
	pthread_mutex_destroy(&g_write);
	pthread_mutex_destroy(g_forks);
	return (NULL);
}

void				free_all(t_philosopher **philos)
{
	t_philosopher	*tmp;
	t_philosopher	*nav;
	int				already;

	nav = *philos;
	already = 0;
	while (!already || (ft_atoi(nav->num) != 1))
	{
		tmp = nav;
		nav = nav->next;
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		else
		{
			pthread_mutex_lock(&tmp->mutex);
			pthread_mutex_destroy(&tmp->mutex);
			free(tmp->num);
			free(tmp);
		}
	}
	pthread_mutex_lock(&nav->mutex);
	pthread_mutex_destroy(&nav->mutex);
	free(nav->num);
	free(nav);
	*philos = close_globals();
}

int					init_threads(t_philosopher **philos)
{
	t_philosopher	*tmp;
	int				already;

	tmp = *philos;
	already = 0;
	g_time_start = get_time_rel();
	while (!already || (ft_atoi(tmp->num) != 1))
	{
		if ((g_error = pthread_create(&(tmp->thread), NULL, philo_life, tmp)))
			return (1);
		pthread_detach(tmp->thread);
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		tmp = tmp->next;
	}
	return (0);
}

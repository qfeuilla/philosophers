/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 19:54:47 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void				take_forks(t_philosopher *philo)
{
	sem_wait(g_forks);
	if (!philo->stop)
	{
		display_msg(philo, get_time_rel(), MS_FORK);
		sem_wait(g_forks);
		if (!philo->stop)
			display_msg(philo, get_time_rel(), MS_FORK);
	}
}

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

void				*philo_life(void *philo_cpy)
{
	pthread_t		monitor;
	pthread_t		monitor2;
	t_philosopher	*philo;

	philo = philo_cpy;
	if (pthread_create(&monitor, NULL, monitor_death, philo_cpy) != 0)
		return ((void*)1);
	pthread_detach(monitor);
	if (pthread_create(&monitor2, NULL, monitor_stop, philo_cpy) != 0)
		return ((void*)1);
	pthread_detach(monitor2);
	usleep(ft_atoi(philo->num) * 100);
	while (!philo->stop)
	{
		if (!philo->stop)
			take_forks(philo);
		if (!philo->stop)
			reat(philo, get_time_rel());
		if (!philo->stop)
			rspleep(philo, get_time_rel());
		if (!philo->stop)
			display_msg(philo, get_time_rel(), MS_THINK);
	}
	return (philo_cpy);
}

void				free_one(t_philosopher *tmp)
{
	sem_wait(tmp->lock);
	sem_post(tmp->full);
	sem_close(tmp->lock);
	sem_close(tmp->full);
	free(tmp->num);
	free(tmp->full_name);
	free(tmp->lock_name);
	free(tmp);
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
			free_one(tmp);
		sem_post(g_forks);
	}
	free_one(nav);
	*philos = NULL;
	sem_post(g_forks);
	sem_close(g_forks);
	sem_close(g_stop);
}

int					init_threads(t_philosopher **philos)
{
	t_philosopher	*tmp;
	int				already;
	pthread_t		monitor;

	tmp = *philos;
	already = 0;
	if (g_eat_num > 0)
	{
		if (pthread_create(&monitor, NULL, monitor_eat, *philos) != 0)
			return (1);
		pthread_detach(monitor);
	}
	usleep(10000);
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

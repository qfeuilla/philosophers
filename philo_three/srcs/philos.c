/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/05 11:47:05 by qfeuilla         ###   ########.fr       */
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

void				philo_life(t_philosopher *philo)
{
	pthread_t		monitor;
	pthread_t		monitor2;

	if (pthread_create(&monitor, NULL, monitor_death, philo) != 0)
		exit(1);
	pthread_detach(monitor);
	if (pthread_create(&monitor2, NULL, monitor_stop, philo) != 0)
		exit(1);
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
	exit(0);
}

void				free_one(t_philosopher *tmp)
{
	sem_wait(tmp->lock);
	sem_post(tmp->full);
	sem_close(tmp->lock);
	sem_close(tmp->full);
	waitpid(tmp->process, NULL, 0);
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
	already = -1;
	while (++already < g_phi_number * 2)
		sem_post(g_forks);
	already = 0;
	while (!already || (ft_atoi(nav->num) != 1))
	{
		tmp = nav;
		nav = nav->next;
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		else
			free_one(tmp);
	}
	free_one(nav);
	*philos = NULL;
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
		if (!(tmp->process = fork()))
			philo_life(tmp);
		if (tmp->process == -1)
			return (1);
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		tmp = tmp->next;
	}
	return (0);
}

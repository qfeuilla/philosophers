/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/01 11:53:19 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void						*philo_life(void *philo_cpy)
{
	t_philosopher	*philo;
	int				time;

	philo = (t_philosopher *)philo_cpy;
	while (1)
		if (g_start)
			break ;
	while (philo->alive && !g_stop)
	{
		time = g_tmp_st;
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop)
			reat(philo);
		if (philo->actual_action == 2 && time >= philo->next_step && !g_stop)
			rspleep(philo);
		if (philo->actual_action == 3 && time >= philo->next_step && !g_stop)
			rthink(philo);
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop)
			reat(philo);
		if (!g_stop)
			if (philo->time_to_die == 0)
				philo->alive = 0;
	}
	return (philo_cpy);
}

void						free_all(t_philosopher **philos)
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
			pthread_join(tmp->thread, NULL);
			free(tmp->num);
			free(tmp);
		}
	}
	free(nav->num);
	free(nav);
}

int							init_threads(t_philosopher **philos)
{
	t_philosopher	*tmp;
	int				already;

	tmp = *philos;
	already = 0;
	while (!already || (ft_atoi(tmp->num) != 1))
	{
		if ((g_error = pthread_create(&(tmp->thread), NULL, philo_life, tmp)))
			return (1);
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		tmp = tmp->next;
	}
	return (0);
}

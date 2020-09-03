/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/02 17:47:09 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void				*philo_life(void *philo_cpy)
{
	t_philosopher	*philo;
	int				time;
	pthread_t		chrono;

	philo = (t_philosopher *)philo_cpy;
	init_life(&chrono, philo);
	while (1)
		if (g_start->__align)
			break ;
	while (philo->alive && !g_stop->__align)
	{
		time = g_tmp_st->__align;
		if ((philo->act_ac == 1 || philo->act_ac == 0) && !g_stop->__align)
			reat(philo);
		if (philo->act_ac == 2 && time >= philo->next_step && !g_stop->__align)
			rspleep(philo);
		if (philo->act_ac == 3 && time >= philo->next_step && !g_stop->__align)
			rthink(philo);
		if (!g_stop->__align)
			rdeath(philo);
	}
	pthread_join(chrono, NULL);
	return (philo_cpy);
}

void				rspleep(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	time = g_tmp_st->__align;
	if (g_phi_number > 1)
	{
		sem_post(g_forks);
		sem_post(g_forks);
	}
	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is sleeping\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->act_ac = 3;
	if (philo->eat_num >= 0)
		philo->eat_num--;
	if (philo->eat_num == 0)
		sem_post(g_philo_full);
	philo->next_step = time + g_time_to_sleep - (time - philo->next_step);
}

void				close_sems(void)
{
	sem_close(g_start);
	sem_close(g_stop);
	sem_close(g_tmp_st);
	sem_close(g_forks);
	sem_close(g_philo_full);
	sem_close(g_philo_turn);
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
		sem_post(g_forks);
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
	close_sems();
}

int					init_threads(t_philosopher **philos)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/30 19:37:40 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void 						*philo_life(void *philo_cpy)
{
	t_philosopher	*philo;
	int				time;

	philo = (t_philosopher *)philo_cpy;
	while (1)
		if (g_start)
			break;
	while (philo->alive && !g_stop)
	{
		time = g_time_stamp;
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop)
			reat(philo);
		if (philo->actual_action == 2 && time >= philo->next_step && !g_stop)
			rspleep(philo);
		if (philo->actual_action == 3 && time >= philo->next_step && !g_stop)
			rthink(philo);
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop)
			reat(philo);
		if (!g_stop)
			rdeath(philo);
	}
	return (philo_cpy);
}

void						rspleep(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	time = g_time_stamp;
	if (g_phi_number > 1)
		pthread_mutex_unlock(&philo->mutex);
	philo->mutex_is_lock = 0;
	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is sleeping\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->actual_action = 3;
	if (philo->eat_num > 0)
		philo->eat_num--;
	if (philo->eat_num == 0)
		philo->alive = 0;
	philo->next_step = time + g_time_to_sleep - (time - philo->next_step);
}

void						rthink(t_philosopher *philo)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is thinking\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->actual_action = 1;
}

void						reat(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	if ((g_phi_number == 1 || (philo->prev && !(philo->prev->mutex_is_lock))) && philo->eat_num != 0)
	{
		philo->mutex_is_lock = 1;
		if (g_phi_number > 1)
			pthread_mutex_lock(&(philo->mutex));
		tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->time_to_die = g_time_to_die;
		time = g_time_stamp;
		tmp_s = ft_strjoin(ft_itoa(time), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " is eating\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->actual_action = 2;
		philo->next_step = time + g_time_to_eat;
	}
}

void						rdeath(t_philosopher *philo)
{
	if (philo->time_to_die == 0)
		philo->alive = 0;
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

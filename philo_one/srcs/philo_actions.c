/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:03:46 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/02 17:40:57 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void						rspleep(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	time = g_tmp_st;
	if (g_phi_number > 1)
		pthread_mutex_unlock(&philo->mutex);
	philo->mutex_is_lock = 0;
	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is sleeping\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->actual_action = 3;
	if (philo->eat_num >= 0)
		philo->eat_num--;
	if (philo->eat_num == 0)
		g_philo_full += 1;
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

void						write_ms_fork(t_philosopher *philo)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(g_tmp_st), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
}

int							reat(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	if ((g_phi_number == 1 || (philo->prev && !(philo->prev->mutex_is_lock))))
	{
		philo->mutex_is_lock = 1;
		if (g_phi_number > 1)
			pthread_mutex_lock(&(philo->mutex));
		write_ms_fork(philo);
		write_ms_fork(philo);
		philo->time_to_die = g_time_to_die;
		time = g_tmp_st;
		tmp_s = ft_strjoin(ft_itoa(time), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " is eating\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->actual_action = 2;
		philo->next_step = time + g_time_to_eat;
		return(1);
	}
	return (0);
}

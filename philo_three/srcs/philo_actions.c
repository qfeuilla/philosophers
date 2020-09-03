/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:03:46 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/03 11:29:34 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void						rthink(t_philosopher *philo)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is thinking\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->act_ac = 1;
}

void						write_ms_fork(t_philosopher *philo)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(g_tmp_st->__align), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
}

void						write_ms_eat(t_philosopher *philo, int time)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(time), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is eating\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
}

int						reat(t_philosopher *philo)
{
	int		time;

	if ((g_phi_number == 1 || (g_forks->__align >= 2 && g_philo_turn->__align == ft_atoi(philo->num))))
	{
		if (g_philo_turn->__align == g_phi_number) {
			g_philo_turn->__align = 1;
		}
		else
			sem_post(g_philo_turn);
		if (!philo->eat_num)
			return (0);
		if (g_phi_number > 1)
		{
			sem_wait(g_forks);
			sem_wait(g_forks);
		}
		if (!g_stop->__align)
		{
			write_ms_fork(philo);
			write_ms_fork(philo);
			philo->time_to_die = g_time_to_die;
			time = g_tmp_st->__align;
			write_ms_eat(philo, time);
			philo->act_ac = 2;
			philo->next_step = time + g_time_to_eat;
		}
		return(1);
	}
	return (0);
}

void						rdeath(t_philosopher *philo)
{
	if ((philo->time_to_die <= 0 && !(reat(philo))) || g_philo_full->__align == g_phi_number)
		philo->alive = 0;
}

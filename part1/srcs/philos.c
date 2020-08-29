/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/29 12:43:42 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void 						*philo_life(void *philo_cpy)
{
	t_philosopher *philo;
	
	philo = (t_philosopher *)philo_cpy;
	while (philo->alive)
	{
		if (philo->actual_action == 1 || philo->actual_action == 0)
			reat(philo);
		if (philo->actual_action == 2 && g_time_stamp >= philo->next_step)
			rspleep(philo);
		if (philo->actual_action == 3 && g_time_stamp >= philo->next_step)
			rthink(philo);
		rdeath(philo);
	}
}

void						rspleep(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	time = g_time_stamp;
	philo->fork_in_hand = 0;
	tmp_s = ft_strjoin(ft_itoa(philo->next_step), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is sleeping\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	philo->actual_action = 3;
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

	time = g_time_stamp;
	if (g_phi_number == 1)
	{
		tmp_s = ft_strjoin(ft_itoa(time), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->fork_in_hand++;
		tmp_s = ft_strjoin(ft_itoa(time), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->fork_in_hand++;
	}
	if (philo->fork_in_hand == 2)
	{
		philo->time_to_die = g_time_to_die;
		tmp_s = ft_strjoin(ft_itoa(time), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " is eating\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->actual_action = 2;
		philo->next_step = time + g_time_to_eat - (time - philo->next_step);
	}
}

void						rdeath(t_philosopher *philo)
{
	if (philo->time_to_die == 0)
		philo->alive = 0;
}

void						free_all(t_philosopher **phi)
{
	
}

int							init_threads(t_philosopher **philos)
{
	t_philosopher	*tmp;
	int				already;

	tmp = *philos;
	already = 0;
	while (!already || (ft_atoi(tmp->num) != 1))
	{
		printf("%s\n", tmp->num);
		if ((g_error = pthread_create(&(tmp->thread), NULL, philo_life, tmp)))
			return (1);
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		tmp = tmp->next;
	}
	return (0);
}

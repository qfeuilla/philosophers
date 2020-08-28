/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/28 14:43:32 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void 						*philo_life(void *philo_cpy)
{
	t_philosopher *philo;
	
	philo = (t_philosopher *)philo_cpy;
	while (1)
	{
		if (reat(philo))
			rspleep(philo);
		else if (!philo->is_thinking)
			rthink(philo);
	}
}

void						rspleep(t_philosopher *philo)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is sleeping\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
	usleep(g_time_to_sleep);
}

void						rthink(t_philosopher *philo)
{
	char	*tmp_s;

	philo->is_thinking= 1;
	tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
	tmp_s = ft_strjoin(tmp_s, philo->num);
	tmp_s = ft_strjoin(tmp_s, " is thinking\n");
	write(1, tmp_s, ft_strlen(tmp_s));
	free(tmp_s);
}

int							reat(t_philosopher *philo)
{
	char	*tmp_s;
	
	if (g_phi_number == 1)
	{
		tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->fork_in_hand++;
		tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		philo->fork_in_hand++;
	}
	if (philo->fork_in_hand == 2)
	{
		philo->is_thinking = 0;
		tmp_s = ft_strjoin(ft_itoa(g_time_stamp), " ");
		tmp_s = ft_strjoin(tmp_s, philo->num);
		tmp_s = ft_strjoin(tmp_s, " is eating\n");
		write(1, tmp_s, ft_strlen(tmp_s));
		free(tmp_s);
		usleep(g_time_to_eat);
		philo->fork_in_hand = 0;
		return (1);
	}
	else
		return (0);
	// return 1 if manage to eat else 0
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

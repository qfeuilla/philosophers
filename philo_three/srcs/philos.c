/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/31 19:56:20 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void						*chronos(void *philo_cpy)
{
	char			*tmp_s;
	t_philosopher	*philo;
	int				i;
	long int		old;

	philo = (t_philosopher *)philo_cpy;
	while (1)
		if (g_start->__align)
			break;
	i = g_stop->__align;
	while (!(i = g_stop->__align))
	{
		if (old != (long int)g_time_stamp->__align)
		{
			philo->time_to_die -= g_time_stamp->__align - old;
			if (philo->alive == 0 || (philo->time_to_die < 0))
			{
				if (philo->eat_num != 0)
				{
					tmp_s = ft_strjoin(ft_itoa(g_time_stamp->__align), " ");
					tmp_s = ft_strjoin(tmp_s, philo->num);
					tmp_s = ft_strjoin(tmp_s, " died\n");
					write(1, tmp_s, ft_strlen(tmp_s));
					free(tmp_s);
				}
				sem_post(g_stop);
				break ;
			}
			old = g_time_stamp->__align;
		}
	}
	return (philo);
}

void 						philo_life(t_philosopher *philo_cpy)
{
	t_philosopher	*philo;
	int				time;
	pthread_t		chrono;
	
	g_start = sem_open(SEM_START, 0);
	g_time_stamp = sem_open(SEM_TIMESTAMP, 0);
	g_stop = sem_open(SEM_STOP, 0);
	philo = (t_philosopher *)philo_cpy;
	pthread_create(&chrono, NULL, chronos, philo);
	while (1)
		if (g_start->__align)
			break;
	while (philo->alive && !g_stop->__align)
	{
		time = g_time_stamp->__align;
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop->__align)
			reat(philo);
		if (philo->actual_action == 2 && time >= philo->next_step && !g_stop->__align)
			rspleep(philo);
		if (philo->actual_action == 3 && time >= philo->next_step && !g_stop->__align)
			rthink(philo);
		if ((philo->actual_action == 1 || philo->actual_action == 0) && !g_stop->__align)
			reat(philo);
		if (!g_stop->__align)
			rdeath(philo);
	}
	pthread_join(chrono, NULL);
}

void						rspleep(t_philosopher *philo)
{
	char	*tmp_s;
	int		time;

	time = g_time_stamp->__align;
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
	
	if ((g_phi_number == 1 || g_forks->__align >= 2) && philo->eat_num != 0)
	{
		if (g_phi_number > 1)
			sem_wait(g_forks);
		if (!g_stop->__align)
		{
			tmp_s = ft_strjoin(ft_itoa(g_time_stamp->__align), " ");
			tmp_s = ft_strjoin(tmp_s, philo->num);
			tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
			write(1, tmp_s, ft_strlen(tmp_s));
			free(tmp_s);
			if (g_phi_number > 1)
				sem_wait(g_forks);
			if (!g_stop->__align)
			{
				tmp_s = ft_strjoin(ft_itoa(g_time_stamp->__align), " ");
				tmp_s = ft_strjoin(tmp_s, philo->num);
				tmp_s = ft_strjoin(tmp_s, " has taken a fork\n");
				write(1, tmp_s, ft_strlen(tmp_s));
				free(tmp_s);
				philo->time_to_die = g_time_to_die;
				time = g_time_stamp->__align;
				tmp_s = ft_strjoin(ft_itoa(time), " ");
				tmp_s = ft_strjoin(tmp_s, philo->num);
				tmp_s = ft_strjoin(tmp_s, " is eating\n");
				write(1, tmp_s, ft_strlen(tmp_s));
				free(tmp_s);
				philo->actual_action = 2;
				philo->next_step = time + g_time_to_eat;
			}
		}
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
		sem_post(g_forks);
		tmp = nav;
		nav = nav->next;
		if (ft_atoi(tmp->num) == 1)
			already = 1;
		else
		{
			waitpid(tmp->process, NULL, 0);
			free(tmp->num);
			free(tmp);
		}
	}
	free(nav->num);
	free(nav);
	sem_close(g_start);
	sem_close(g_stop);
	sem_close(g_time_stamp);
	sem_close(g_forks);
	
}

int							init_threads(t_philosopher **philos)
{
	t_philosopher	*tmp;
	int				already;

	tmp = *philos;
	already = 0;
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

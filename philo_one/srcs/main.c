/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:03:02 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/01 13:54:31 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

/*
** change the time to scale 1:TIMESCALE
*/

#define TIMESCALE 1

int				timediff(struct timeval t1, struct timeval t2)
{
	return (((t1.tv_sec - t2.tv_sec) * 1000000) +
			(t1.tv_usec - t2.tv_usec)) / 1000;
}

void			manage_die(t_philosopher *philo)
{
	char	*tmp_s;

	--philo->time_to_die;
	if (philo->alive == 0)
	{
		if (philo->eat_num != 0)
		{
			tmp_s = ft_strjoin(ft_itoa(g_tmp_st), " ");
			tmp_s = ft_strjoin(tmp_s, philo->num);
			tmp_s = ft_strjoin(tmp_s, " died\n");
			write(1, tmp_s, ft_strlen(tmp_s));
			free(tmp_s);
		}
		g_stop = 1;
	}
}

void			loop(t_philosopher **philos)
{
	t_philosopher	*tmp;
	struct timeval	time1;
	struct timeval	time2;

	if (init_threads(philos))
		return ;
	g_start = 1;
	while (!g_stop)
	{
		gettimeofday(&time1, NULL);
		tmp = (*philos)->next;
		manage_die(*philos);
		while (tmp != *philos)
		{
			manage_die(tmp);
			tmp = tmp->next;
		}
		gettimeofday(&time2, NULL);
		usleep(1000 * TIMESCALE - timediff(time1, time2));
		g_tmp_st++;
	}
}

int				manage_errors(void)
{
	if (g_error == EINVAL)
		write(2, MS_EINVAL, ft_strlen(MS_EINVAL));
	if (g_error == EFAULT)
		write(2, MS_EFAULT, ft_strlen(MS_EFAULT));
	if (g_error == EAGAIN)
		write(2, MS_EAGAIN, ft_strlen(MS_EAGAIN));
	if (g_error == -1)
		write(2, MS_ARG, ft_strlen(MS_ARG));
	return (1);
}

int				main(int ac, char **av)
{
	t_philosopher *philos;

	g_start = 0;
	g_stop = 0;
	g_tmp_st = 0;
	g_error = 0;
	g_eat_num = -1;
	g_philo_full = 0;
	philos = init_phis(av, ac);
	if (philos)
	{
		loop(&philos);
		free_all(&philos);
	}
	if (g_error)
		return (manage_errors());
	return (0);
}

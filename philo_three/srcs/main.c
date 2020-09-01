/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:03:02 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/01 11:07:03 by qfeuilla         ###   ########.fr       */
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

void			loop(t_philosopher **philos)
{
	if (init_threads(philos))
		return ;
	sem_post(g_start);
	while (!g_stop->__align)
	{
		usleep(1000);
		sem_post(g_tmp_st);
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

	sem_unlink("/forks");
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_TIMESTAMP);
	sem_unlink(SEM_START);
	g_tmp_st = 0;
	g_error = 0;
	philos = init_phis(av, ac);
	if (philos)
	{
		loop(&philos);
		free_all(&philos);
		sem_close(g_forks);
	}
	if (g_error)
		return (manage_errors());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:03:02 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 19:25:14 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

int				timediff(struct timeval t1, struct timeval t2)
{
	return (((t1.tv_sec - t2.tv_sec) * 1000000) +
			(t1.tv_usec - t2.tv_usec)) / 1000;
}

void			loop(t_philosopher **philos)
{
	t_philosopher	*nav;

	nav = *philos;
	init_threads(philos);
	while (!g_stop)
		;
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
	if (g_error == -2)
		write(2, MS_ALLOCF, ft_strlen(MS_ALLOCF));
	return (1);
}

pthread_mutex_t	*init_mutexs(void)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	if (!(forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* g_phi_number)))
		return (NULL);
	while (++i < g_phi_number)
		pthread_mutex_init(&(forks[i]), NULL);
	return (forks);
}

int				main(int ac, char **av)
{
	t_philosopher *philos;

	g_stop = 0;
	g_error = 0;
	g_eat_num = -1;
	g_philo_full = 0;
	g_time_start = 0;
	pthread_mutex_init(&g_write, NULL);
	philos = init_phis(av, ac);
	if (!(g_forks = init_mutexs()))
		free_all(&philos);
	if (philos)
	{
		loop(&philos);
		usleep(100000);
		free_all(&philos);
	}
	if (g_error)
		return (manage_errors());
	return (0);
}

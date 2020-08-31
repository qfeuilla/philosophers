/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:03:02 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/31 19:45:47 by qfeuilla         ###   ########.fr       */
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
		sem_post(g_time_stamp);
	}
}

t_philosopher	*creat_philo(t_philosopher *prev, int i, int eat_num)
{
	t_philosopher	*philo;

	if (!(philo = malloc(sizeof(t_philosopher))))
		return (NULL);
	philo->eat_num = eat_num;
	philo->time_to_die = g_time_to_die;
	philo->num = ft_itoa(i + 1);
	philo->alive = 1;
	philo->actual_action = 0;
	philo->next_step = 0;
	philo->prev = prev;
	philo->next = NULL;
	if (prev)
		prev->next = philo;
	return (philo);
}

t_philosopher	*init_util(int ac, char **av, int i)
{
	int				bool;
	t_philosopher	*phis;
	t_philosopher	*tmp;


	bool = 0;
	if (ac == g_phi_number + 5)
		bool = 1;
	if (bool)
		phis = creat_philo(NULL, i, ft_atoi(av[i + 5]));
	else
		phis = creat_philo(NULL, i, -1);
	tmp = phis;
	while (++i < g_phi_number)
	{
		if (bool)
			tmp = creat_philo(tmp, i, ft_atoi(av[i + 5]));
		else
			tmp = creat_philo(tmp, i, -1);
	}
	tmp->next = phis;
	phis->prev = tmp;
	g_forks = sem_open("/forks", O_CREAT, 0664, (long unsigned)g_phi_number);
	g_stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	g_time_stamp = sem_open(SEM_TIMESTAMP, O_CREAT, 0644, 0);
	g_start = sem_open(SEM_START, O_CREAT, 0664, 0);
	return (phis);
}

t_philosopher	*init_phis(char **av, int ac)
{
	if (ac <= 4)
	{
		g_error = -1;
		return (NULL);
	}
	g_phi_number = ft_atoi(av[1]);
	if (g_phi_number < 1)
		return (NULL);
	g_time_to_die = ft_atoi(av[2]);
	g_time_to_eat = ft_atoi(av[3]);
	g_time_to_sleep = ft_atoi(av[4]);
	if (ft_atoi(av[2]) == 0)
	{
		write(1, "0 1 died\n", 9);
		return (NULL);
	}
	return (init_util(ac, av, 0));
}

int				manage_errors()
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
	g_time_stamp = 0;
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
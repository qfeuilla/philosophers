/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 01:09:45 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 20:21:21 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

t_philosopher	*creat_philo(t_philosopher *prev, int i, int eat_num)
{
	t_philosopher	*philo;

	if (!(philo = malloc(sizeof(t_philosopher))))
		return (NULL);
	philo->eat_num = eat_num;
	philo->dead_limit = g_time_to_die;
	philo->num = ft_itoa(i + 1);
	philo->alive = 1;
	philo->full_name = make_name(SEM_FULL, i + 1);
	philo->full = ft_sem_open(philo->full_name, 0);
	philo->lock_name = make_name(SEM_LOCK, i + 1);
	philo->lock = ft_sem_open(philo->lock_name, 1);
	philo->stop = 0;
	philo->step = 0;
	if (prev)
		prev->next = philo;
	return (philo);
}

t_philosopher	*init_util(int ac, char **av, int i)
{
	t_philosopher	*phis;
	t_philosopher	*tmp;

	if (ac == 6)
		g_eat_num = ft_atoi(av[5]);
	if (g_eat_num == 0)
		return (NULL);
	phis = creat_philo(NULL, i, g_eat_num);
	tmp = phis;
	while (++i < g_phi_number)
		tmp = creat_philo(tmp, i, g_eat_num);
	tmp->next = phis;
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

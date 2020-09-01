/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 01:09:45 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/01 12:07:36 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

t_philosopher	*creat_philo(t_philosopher *prev, int i, int eat_num)
{
	t_philosopher	*philo;

	if (!(philo = malloc(sizeof(t_philosopher))))
		return (NULL);
	philo->eat_num = eat_num;
	philo->time_to_die = g_time_to_die;
	philo->num = ft_itoa(i + 1);
	philo->alive = 1;
	philo->act_ac = 0;
	philo->next_step = 0;
	philo->prev = prev;
	philo->next = NULL;
	if (prev)
		prev->next = philo;
	return (philo);
}

int				one_is_zero(char **av, int i)
{
	while (i < g_phi_number)
	{
		if (!ft_atoi(av[i + 5]))
			return (1);
		i++;
	}
	return (0);
}

void			create_sem(void)
{
	g_forks = sem_open("/forks", O_CREAT, 0664, (long unsigned)g_phi_number);
	g_stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	g_tmp_st = sem_open(SEM_TIMESTAMP, O_CREAT, 0644, 0);
	g_start = sem_open(SEM_START, O_CREAT, 0664, 0);
}

t_philosopher	*init_util(int ac, char **av, int i)
{
	int				bool;
	t_philosopher	*phis;
	t_philosopher	*tmp;

	bool = 0;
	if (ac == g_phi_number + 5 && one_is_zero(av, 0))
		return (NULL);
	if (ac == g_phi_number + 5)
		bool = 1;
	if (bool)
		phis = creat_philo(NULL, i, ft_atoi(av[i + 5]));
	else
		phis = creat_philo(NULL, i, -1);
	tmp = phis;
	while (++i < g_phi_number)
		if (bool)
			tmp = creat_philo(tmp, i, ft_atoi(av[i + 5]));
		else
			tmp = creat_philo(tmp, i, -1);
	tmp->next = phis;
	phis->prev = tmp;
	create_sem();
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

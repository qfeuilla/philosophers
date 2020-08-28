/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:10:32 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/28 13:38:41 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

void 						*philo_life(void *philo_cpy)
{
	
}

void						rspleep(t_philosopher *philo)
{

}

void						rthink(t_philosopher *philo)
{
	
}

int							reat(t_philosopher *philo)
{
	
}

void						free_all(t_philosopher **phi)
{
	
}

int							init_threads(t_philosopher **philos)
{
	t_philosopher *tmp;

	tmp = *philos;
	while (tmp) 
	{
		if (!(g_error = pthread_create(&tmp->thread, NULL, philo_life, NULL)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

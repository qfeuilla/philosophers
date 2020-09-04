/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 00:57:47 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/01 00:59:31 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

static int	countchar(int n)
{
	int				count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
	{
		count++;
		nb = (unsigned int)-n;
	}
	else
		nb = (unsigned int)n;
	while (nb / 10 > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int				i;
	char			*tab;
	unsigned int	nb;

	i = countchar(n);
	if (!(tab = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
	{
		nb = (unsigned int)-n;
		tab[0] = '-';
	}
	else
		nb = (unsigned int)n;
	tab[i] = '\0';
	i--;
	while (i >= 0)
	{
		tab[i] = nb % 10 + 48;
		nb = nb / 10;
		if (nb == 0)
			break ;
		i--;
	}
	return (tab);
}

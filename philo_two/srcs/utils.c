/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:00:40 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 19:16:31 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philosophers.h"

int			ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*destptr;
	const char	*srcptr;

	if (src == NULL && dst == NULL)
		return (dst);
	if (dst < src)
	{
		destptr = dst;
		srcptr = src;
		while (n--)
			*destptr++ = *srcptr++;
	}
	else
	{
		destptr = dst + n - 1;
		srcptr = src + n - 1;
		while (n--)
			*destptr-- = *srcptr--;
	}
	return (dst);
}

char		*ft_strjoin(char const *s1, char const *s2, int fre)
{
	char			*strj;
	unsigned int	len1;
	unsigned int	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(strj = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	ft_memmove(strj, s1, len1);
	ft_memmove(strj + len1, s2, len2);
	strj[len1 + len2] = '\0';
	if (fre)
	{
		if (fre == 1)
			free((char *)s1);
		else
			free((char *)s2);
	}
	return (strj);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int rvalue;

	i = 0;
	sign = 0;
	rvalue = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] >= '0' && str[i] <= '9')
			rvalue = rvalue * 10 + (str[i] - 48);
		i++;
	}
	return ((sign >= 0 || sign % 2 == 0) ? (rvalue) : (-rvalue));
}

void		display_msg(t_philosopher *philo, int time, char *msg)
{
	char	*tmp_s;

	tmp_s = ft_strjoin(ft_itoa(time), " ", 1);
	tmp_s = ft_strjoin(tmp_s, philo->num, 1);
	tmp_s = ft_strjoin(tmp_s, msg, 1);
	sem_wait(g_write);
	write(1, tmp_s, ft_strlen(tmp_s));
	sem_post(g_write);
	free(tmp_s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:45:55 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/09/04 13:47:37 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERRORS_H
# define PHILO_ERRORS_H

# include <errno.h>

# define MS_EAGAIN "Not enougth ressources to create another thread\n"

# define MS_EFAULT "Thread or attr is an invalid pointer.\n"

# define MS_EINVAL "Attr is not an initialized thread attribute object.\n"

# define MS_ARG "Too few arguments for input\n"

# define MS_ALLOCF "Error when trying to allocate forks"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:45:55 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/28 14:50:19 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <errno.h>

#define MS_EAGAIN "The system lacked the necessary resources to create \n\
				another thread, or the system-imposed limit on the total \n \
				number of threads in a process PTHREAD_THREADS_MAX would \n \
				be exceeded.\n"

#define MS_EFAULT "Thread or attr is an invalid pointer.\n"

#define MS_EINVAL "Attr is not an initialized thread attribute object.\n"

#define MS_ARG "Too few arguments for input\n"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:45:55 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/28 13:51:32 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MS_EAGAIN "The system lacked the necessary resources to create another\
				 thread, or the system-imposed limit on the total number of \
				threads in a process PTHREAD_THREADS_MAX would be exceeded."

#define MS_EFAULT "Thread or attr is an invalid pointer."

#define MS_EINVAL "Attr is not an initialized thread attribute object."

#define MS_ARG "Too few arguments for input"
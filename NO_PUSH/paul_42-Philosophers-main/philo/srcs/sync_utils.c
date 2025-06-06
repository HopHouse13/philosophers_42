/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:28:09 by phautena          #+#    #+#             */
/*   Updated: 2025/06/06 15:28:00 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_bool(t_mtx *mutex, bool *value, bool to_set)
{
	pthread_mutex_lock(mutex);
	*value = to_set;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_long(t_mtx *mutex, long *value, long to_set)
{
	pthread_mutex_lock(mutex);
	*value = to_set;
	pthread_mutex_unlock(mutex);
}

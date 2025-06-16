/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:22:11 by pab               #+#    #+#             */
/*   Updated: 2025/06/16 12:42:19 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_set_bool(pthread_mutex_t	*lock, bool	*value, bool update)
{
	pthread_mutex_lock(lock);
	*value = update;
	pthread_mutex_unlock(lock);
}

bool	ft_get_bool(pthread_mutex_t *lock, bool *value)
{
	bool	result;
	
	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}

void	ft_set_long(pthread_mutex_t	*lock, long	*value, long update)
{
	pthread_mutex_lock(lock);
	*value = update;
	pthread_mutex_unlock(lock);
}

long	ft_get_long(pthread_mutex_t *lock, long *value)
{
	long	result;
	
	pthread_mutex_lock(lock);
	result = *value;
	pthread_mutex_unlock(lock);
	return (result);
}
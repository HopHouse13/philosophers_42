/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:11:34 by pbret             #+#    #+#             */
/*   Updated: 2025/06/26 19:36:46 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (&data->forks[i])
			pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->time_lock);
	pthread_mutex_destroy(&data->meat_lock);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

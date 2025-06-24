/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:45:02 by pbret             #+#    #+#             */
/*   Updated: 2025/06/24 20:28:37 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	ft_safe_write(philo, &data->write_lock, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	ft_safe_write(philo, &data->write_lock, "has taken a fork");

	philo->nb_meals++;
	if (philo->nb_meals >= data->must_eat)
	philo->ifinished = true;
	ft_safe_write(philo, &data->write_lock, "is eating");
	ft_precise_waiting(data, data->tt_eat);
	ft_set_long(&data->time_lock, &philo->last_meal, get_time());

	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	ft_sleep(t_data *data, t_philo *philo)
{
	ft_safe_write(philo, &data->write_lock, "is sleeping");
	ft_precise_waiting(data, data->tt_sleep);
}

void	ft_think(t_data *data, t_philo *philo)
{
	ft_safe_write(philo, &data->write_lock, "is thinking");
	ft_precise_waiting(data, data->tt_think);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:29:46 by pab               #+#    #+#             */
/*   Updated: 2025/06/25 20:38:44 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Conditions:
// ctrl c
// si un philo meurt (time - last_meal < tt_die)
// si tout les philo ont manger must_eat fois
void	ft_monitor(t_data *data)
{
	int		i;
	int		eat_count;

	eat_count = 0;
	while (data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if ((get_time() - ft_get_long(&data->time_lock,
						&data->philos[i].last_meal)) >= data->tt_die)
			{
				ft_safe_write(&data->philos[i], &data->write_lock, "died");
				ft_set_bool(&data->end_lock, &data->end, true);
				break ;
			}
			if (data->philos[i].ifinished == true)
				eat_count++;
		}
		if (data->must_eat != -1 && eat_count >= data->nb_philo)
		{	
			ft_set_bool(&data->end_lock, &data->end, true);
			//ft_safe_write(); // afficher un message en debut et fin de simulation et message en rouge pour le philo dead
		}
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (ft_get_bool(&data->start_lock, &data->start) == false)
		;
	ft_set_long(&data->time_lock, &philo->last_meal, get_time());
	if (data->nb_philo == 1)
		return (ft_only_one(philo));
	if (philo->id % 2)
		ft_precise_waiting(data, 60);
	while (ft_get_bool(&data->end_lock, &data->end) == false)
	{
		if (ft_get_bool(&data->end_lock, &data->end) == false)
			ft_eat(data, philo);
		if (ft_get_bool(&data->end_lock, &data->end) == false)
			ft_sleep(data, philo);
		if (ft_get_bool(&data->end_lock, &data->end) == false)
			ft_think(data, philo);
	}
	return (NULL);
}

bool	ft_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine,
				&data->philos[i]) != 0)
			return (printf("Error with creating a thread\n"));
	}
	ft_set_long(&data->time_lock, &data->time, get_time());
	ft_set_bool(&data->start_lock, &data->start, true);
	ft_precise_waiting(data, 60);
	ft_monitor(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error with joining a thread\n"));
	}
	return (false);
}

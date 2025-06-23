/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:29:46 by pab               #+#    #+#             */
/*   Updated: 2025/06/23 20:43:32 by pbret            ###   ########.fr       */
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
	// long	t_last_meal;
	
	ft_precise_waiting(data, 60);
	while(data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->eat_lock);
			//t_last_meal = (ft_get_time() - ft_get_long(&data->time_lock, &data->philos[i].last_meal));
			if (ft_get_time() - ft_get_long(&data->time_lock, &data->philos[i].last_meal) >= data->tt_die)
			{
				ft_safe_write(&data->philos[i],&data->write_lock, "died");
				data->end = true;
				pthread_mutex_unlock(&data->eat_lock);
				break;
			}
			pthread_mutex_unlock(&data->eat_lock);
			// if (data->must_eat != -1 && data->philos[i].nb_meals == data->must_eat) // la je teste si un philo a mange suffisament de repas; pas si tous les philo ont manges suffisament de repas		
		}
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	while (ft_get_bool(&data->start_lock, &data->start) == false) // en attente que tout les threads soient init
		;
	//only_one; 
	ft_set_long(&data->time_lock, &philo->last_meal, ft_get_time());
	if (philo->id % 2)
		ft_precise_waiting(data, 60);
	while (ft_get_bool(&data->end_lock, &data->end) == false)
	{
		pthread_mutex_lock(philo->first_fork);
		ft_safe_write(philo, &data->write_lock, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		ft_safe_write(philo, &data->write_lock, "has taken a fork");
		ft_set_long(&data->time_lock, &philo->last_meal, ft_get_time());
		ft_set_int(&data->must_eat_lock, &philo->nb_meals, philo->nb_meals++); // pas sur
		ft_safe_write(philo, &data->write_lock, "is eating");
		ft_precise_waiting(data, data->tt_eat);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		ft_safe_write(philo, &data->write_lock, "is sleeping");
		ft_precise_waiting(data, data->tt_sleep);
		ft_safe_write(philo, &data->write_lock, "is thinking");
		// ft_tt_think;
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
	ft_set_long(&data->time_lock, &data->time, ft_get_time()); // init data-> time qui est le time pour tous les philo
	ft_set_bool(&data->start_lock, &data->start, true); // depart
	ft_monitor(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error with joining a thread\n"));
	}
	return (false);
}

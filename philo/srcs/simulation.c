/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:29:46 by pab               #+#    #+#             */
/*   Updated: 2025/06/17 22:34:14 by pbret            ###   ########.fr       */
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

	while(data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{printf ("time_eat_philo -> %ld\ttt_die -> %ld\n\n", ft_upt(data->philos[i].last_meal), data->tt_die);
			if (ft_upt(data->philos[i].last_meal) > data->tt_die)
			{
				ft_safe_write(&data->philos[i],&data->write_lock, "died");
				data->end = !data->end;
				break;
			}
				// if (data->must_eat != 1 && data->philos[i].nb_meals > data->must_eat) // la je teste si un philo a mange suffisament de repas; pas si tous les philo ont manges suffisament de repas
				// {
				// 	data->end = !data->end;
				// 	break;
				// }
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
	ft_set_long(&data->time_lock, &philo->last_meal, ft_get_time());
	if (philo->id % 2)
		ft_precise_waiting(data->nb_philo, 60);
	while (ft_get_bool(&data->end_lock, &data->end) == false)
	{
		pthread_mutex_lock(philo->first_fork);
		ft_safe_write(philo, &data->write_lock, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		ft_safe_write(philo, &data->write_lock, "has taken a fork");
		ft_safe_write(philo, &data->write_lock, "is eating");
		ft_precise_waiting(data->nb_philo, data->tt_eat);
		philo->last_meal = ft_upt(data->time);
		philo->nb_meals++;
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		ft_safe_write(philo, &data->write_lock, "is sleeping");
		ft_precise_waiting(data->nb_philo, data->tt_sleep);
		ft_safe_write(philo, &data->write_lock, "is thinking");
	}
	return (NULL);
}

bool	ft_simulation(t_data *data)
{
	int	i;

	// data->test_kikikiaparle = 1; //ASUPP
	// pthread_mutex_init(&data->test_lock, NULL);
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
	{printf("fermeture du thread N%d\n", data->philos[i].id);
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error with joining a thread\n"));
	}
	return (false);
}
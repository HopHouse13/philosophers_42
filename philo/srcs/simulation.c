/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:29:46 by pab               #+#    #+#             */
/*   Updated: 2025/06/24 20:55:30 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


// void	ft_must_eat(t_data *data)
// {
// 	int	i;
// 	int	eat_count;
	
// 	eat_count = 0;
// 	i = -1;
// 	if(data->must_eat == -1)
// 		return ;
// 	while (++i < data->nb_philo)
// 	{
// 		pthread_mutex_lock(&data->must_eat_lock);
// 		if (data->philos[i].nb_meals >= data->must_eat)
// 		{
// 			// printf("PHILO N%d INCREASE    NBMEAL: %d\n", data->philos[i].id, data->philos[i].nb_meals);
// 			eat_count++;
// 		}
// 		pthread_mutex_unlock(&data->must_eat_lock);
// 	}
// 	// printf("value_eat_count >> [%d]\tvalue_nb_philo >> [%d]\n", eat_count, data->nb_philo);
// 	if (eat_count >= data->nb_philo)
// 		ft_set_bool(&data->end_lock, &data->end, true);
// 	eat_count = 0;
// }

// Conditions:
// ctrl c
// si un philo meurt (time - last_meal < tt_die)
// si tout les philo ont manger must_eat fois
void	ft_monitor(t_data *data)
{
	int		i;
	int	eat_count;
	
	eat_count = 0;
	while(data->end == false)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->eat_lock);
			if ((get_time() - ft_get_long(&data->time_lock, &data->philos[i].last_meal))
					>= data->tt_die)
			{
				ft_safe_write(&data->philos[i],&data->write_lock, "died");
				ft_set_bool(&data->end_lock, &data->end, true);
				pthread_mutex_unlock(&data->eat_lock);
				break ;
			}
			pthread_mutex_unlock(&data->eat_lock);
			if (data->philos[i].ifinished == true)
				eat_count++;
		}
		if (data->must_eat != -1 && eat_count >= data->nb_philo)
			ft_set_bool(&data->end_lock, &data->end, true);
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
	ft_set_long(&data->time_lock, &data->time, get_time()); // init data-> time qui est le time pour tous les philo
	ft_set_bool(&data->start_lock, &data->start, true); // depart
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
	
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:29:46 by pab               #+#    #+#             */
/*   Updated: 2025/06/16 14:09:29 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	kikikiaparle(t_philo *philo)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->data->test_lock);
// 		if (philo->id == philo->data->test_kikikiaparle)
// 		{
// 			printf("bonjour! Je suis le philo N%d!\n", philo->id);
// 			philo->data->test_kikikiaparle++;
// 			pthread_mutex_unlock(&philo->data->test_lock);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&philo->data->test_lock);
// 	}
// }

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_get_bool(&philo->data->start_lock, &philo->data->start) == false)
		;
	//kikikiaparle(philo);
	ft_set_long(&philo->data->time_lock, &philo->last_meal, ft_get_time());
	if (philo->id % 2)
		ft_precise_sleep(philo->data->nb_philo, 60);
	while (ft_get_bool(&philo->data->end_lock, &philo->data->end) == false)
	{
		
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
	{printf("crea du thread N%d\n", data->philos[i].id);
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine,
				&data->philos[i]) != 0)
			return (printf("erreur de creation d'un thread\n"));
	}
	ft_set_long(&data->time_lock, &data->time, ft_get_time()); // init data-> time qui est le time pour tous les philo
	ft_set_bool(&data->start_lock, &data->start, true); // depart
	i = -1;
	while (++i < data->nb_philo)
	{printf("fermeture du thread N%d\n", data->philos[i].id);
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("erreur de connection d'un threads\n"));
	}
	return (false);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:25:01 by phautena          #+#    #+#             */
/*   Updated: 2025/06/13 10:53:07 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_free(t_data *data) //Fonction free pour toute notre structure data
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->must_eat_lock);
	pthread_mutex_destroy(&data->start_lock);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->time_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init_all(&data, argv) != 0)
			return (1);
		if (start_simulation(&data) != 0)
			return (2);
		ft_free(&data); //Une fois que la simulation est finie, on free nos structures et destroy nos mutexes
	}
	else
		return (printf("./philo <nb_philo> <tdie> <teat> <tsleep> [eat_n]"));
}

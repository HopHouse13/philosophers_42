/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:32:49 by pab               #+#    #+#             */
/*   Updated: 2025/06/16 12:36:17 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/philo.h"

void	ft_init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i +1;
		data->philos[i].nb_meals = data->must_eat;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		if (data->philos[i].id % 2)
		{
			data->philos[i].first_fork = &data->forks[i];
			data->philos[i].second_fork = &data->forks[i +1 % data->nb_philo];
		}
		else
		{
			data->philos[i].first_fork = &data->forks[i +1 % data->nb_philo];
			data->philos[i].second_fork = &data->forks[i];
		}
	}
}
 
bool	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return	(false);
	if (pthread_mutex_init(&data->eat_lock, NULL) != 0)
		return	(false);
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		return	(false);
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		return	(false);
	if (pthread_mutex_init(&data->time_lock, NULL) != 0)
		return	(false);
	return (true);
}
 
bool	ft_init_tabs(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos || !data->forks)
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
		data->philos = NULL;
		data->forks = NULL;
		return (false);
	}
	return (true);
}

void	ft_init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[2]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat =ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->time = 0;
	data->end = false;
	data->start = false;
}

bool	ft_initialisation(t_data *data, char **argv)
{
	ft_init_data(data, argv);
	if (!ft_init_tabs(data))
		return (printf("Erreur d'allocation memoire"));
	if (!ft_init_mutex(data))
		return (printf("Erreur lors de l'initilialisation d'un mutex"));
	ft_init_philo(data);
	return (false);
}

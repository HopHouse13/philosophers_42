/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:32:49 by pab               #+#    #+#             */
/*   Updated: 2025/06/13 16:42:58 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/philo.h"

bool	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
	}
	return	(true);
}
 
bool	ft_init_tab_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos)
	{
		data->philos = NULL;
		return (false);
	}
	return (true);
}

bool	ft_init_tab_philo(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		data->philos = NULL;
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
		data->nb_meal =ft_atoi(argv[5]);
	else
		data->nb_meal = -1;
	// data->end = false; je sais pas encore ce que c'est emcore.
	// data->start = false;
}

bool	ft_initialisation(t_data *data, char **argv)
{
	ft_init_args(data, argv);
	if (!ft_init_tab_philo(data))
		return (printf("Erreur d'allocation de memoire pour les philos"));
	if (!ft_init_tab_forks(data))
		return (printf("Erreur d'allocation de memoire pour les fourchettes"));
	if (!ft_init_mutex(data))
		return (printf("Erreur lors de l'initilialisation d'un mutex"));
	ft_init_philo(data);
	
	return (false);
}

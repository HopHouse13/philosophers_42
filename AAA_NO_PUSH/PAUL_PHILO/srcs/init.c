/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:35 by phautena          #+#    #+#             */
/*   Updated: 2025/06/14 15:03:47 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i + 1; //On attribue les IDentifiants aux philos, avec un +1 car on ne veux pas de philos n*0
		data->philos[i].must_eat_n = 0;
		data->philos[i].data = data;
		if (data->philos[i].id % 2) //Ici, on attribue des fourchette differentes aux philos afin de ne pas avoir de probleme de syncronisation/deadlock (meme raison que pour laquelle on fait un sleep de 60ms dans la routine des philos, voir BlogPost dans le pastebin pour mieux comprendre)
		{
			data->philos[i].first_fork = &data->forks[i];
			data->philos[i].second_fork = &data->forks[(i +1) % data->nb_philo];
		}
		else
		{
			data->philos[i].first_fork = &data->forks[(i +1) % data->nb_philo];
			data->philos[i].second_fork = &data->forks[i];
		}
	}
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = -1; //Initialisation de tous les mutex
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error while initializing forks mutexes\n"));
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (printf("Error while initializing write_lock mutex\n"));
	if (pthread_mutex_init(&data->must_eat_lock, NULL) != 0)
		return (printf("Error while initializing must_eat_lock mutex\n"));
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		return (printf("Error while initializing start_lock mutex\n"));
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		return (printf("Error while initializing end_lock mutex\n"));
	if (pthread_mutex_init(&data->time_lock, NULL) != 0)
		return (printf("Error while initializing time_lock mutex\n"));
	return (0);
}

static int	parse_argv(t_data *data, char *argv[])
{
	data->nb_philo = ft_atoi(argv[1]); //Parsing des arguments donnes par l'utilisateur
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->nb_philo == -1 || data->tt_die == -1 //Le ft_atoi renvoie -1 si un autre charactere que des chiffres est entre
		|| data->tt_eat == -1 || data->tt_sleep == -1)
		return (printf("Arguments are invalid\n"));
	if (argv[5])
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == -1)
			return (printf("Arguments are invalid\n"));
	}
	else
		data->must_eat = -1; // Si jamais le cinquieme argument n'est pas donne, cette variable est a -1 pour dire que rien n'a ete donne et que ca ne sert a rien de checker le nombre de fois ou ils ont mange
	if (data->nb_philo < 1 || data->nb_philo > 200)
		return (printf("Incorrect number of philos\n"));
	if (data->tt_die < 60 || data->tt_eat < 60 || data->tt_sleep < 60) //On accepte pas les valeurs en dessous de 60ms pour des raisons de precision
		return (printf("Please do not use time < 60ms\n"));
	return (0);
}

static int	init_data(t_data *data, char *argv[])
{
	if (parse_argv(data, argv) != 0) //Parsing des arguments
		return (1);
	data->end = false; //Mise a false des booleans
	data->start = false;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo); //Maloc d'un tableau de philos
	if (!data->philos)
		return (printf("Error while allocating memory for philos\n"));
	data->forks = malloc(sizeof(t_mtx) * data->nb_philo); //Malloc d'un tableau de mutex (representant nos fourchettes)
	if (!data->forks)
		return (printf("Error while allocating memory for forks\n"));
	if (init_mutexes(data) != 0)
		return (2);
	return (0);
}

int	init_all(t_data *data, char *argv[])
{
	if (init_data(data, argv) != 0)
		return (1);
	init_philos(data);
	return (0);
}

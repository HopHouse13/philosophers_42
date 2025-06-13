/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:37:06 by phautena          #+#    #+#             */
/*   Updated: 2025/06/13 19:58:04 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lone_philo(t_data *data)
{
	//Si il n'y a qu'un seul philo, il n'y a donc qu'une seule fourchette. Tout ce que fait ce philo est donc d'attraper une fourchette, et attendre la mort (checkee par le monitor)... C'EST TRISTE PUTAIN
	pthread_mutex_lock(data->philos[0].first_fork);
	safe_write(&data->philos[0], "has taken a fork");
	pthread_mutex_unlock(data->philos[0].first_fork);
}

void	safe_write(t_philo *philo, char *status)
{
	t_data	*data;
	t_mtx	*tlock;
	long	tstart;

	data = philo->data; //Cette fonction permet a chaque philo d'ecrire son statut sur le terminal de maniere securisee, le write_lock permet que les philos attendent que le precedent ait fini d'ecrire avant de commencer
	tlock = &data->time_lock;
	tstart = data->start_time;
	pthread_mutex_lock(&data->end_lock);
	if (data->end == false)
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld ", get_time() - get_long(tlock, &tstart));
		printf("%d ", philo->id);
		printf("%s\n", status);
		pthread_mutex_unlock(&data->write_lock);
	}
	pthread_mutex_unlock(&data->end_lock);
}

long	get_time(void) //Fonction horrible de formatage de l'horaire. (Utile pour mettre les timestamps des action des philos. Pour comprendre, "man gettimeofday" sur google)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("Error while using gettimeofday()\n"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	precise_sleep(long usec) //Le usleep de la librairie C standard n'est pas tres preci, on recree donc le notre. A expliquer IRL
{
	long	start;

	start = get_time();
	while ((get_time() - start) < usec)
		usleep(500);
}

long	ft_atoi(const char *nptr)
{
	int		i;
	int		j;
	long	result;

	i = 0;
	result = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	j = i - 1;
	while (nptr[++j])
	{
		if (nptr[j] < 48 || nptr[j] > 57)
			return (-1);
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:26:27 by phautena          #+#    #+#             */
/*   Updated: 2025/06/13 19:44:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_all_ate(t_data *data)
{
	int	i;
	int	ate;

	i = -1;
	ate = 0;
	while (++i < data->nb_philo) //Pour checker l'argument optionnel, on loop a travers tous les philos, et regarde si ils ont TOUS mange AU MOINS le nombre qu'ils devraient
	{
		pthread_mutex_lock(&data->must_eat_lock);
		if (data->philos[i].must_eat_n >= data->must_eat)
			ate++;
		pthread_mutex_unlock(&data->must_eat_lock);
	}
	if (ate == data->nb_philo) //Si ils ont tous mange au moins "must_eat" fois (argument optionnel passe par l'utilisateur), alors on mettra la variable "end" a true (voir fonction parent)
		return (true);
	return (false);
}

static void	 monitor(t_data *data)
{
	int		i;
	long	last_meal;

	precise_sleep(60); //On attend 60ms afin de s'assurer que tous les threads de philo sont bien lances
	while (data->end == false) //On loop tant que la simulation n'est pas terminee
	{
		i = -1;
		while (++i < data->nb_philo) //On va loop a travers tous les philos et bien verifie qu'ils ne sont pas morts
		{
			last_meal = get_long(&data->time_lock, &data->philos[i].last_meal); //On recupere l'horaire de la derniere fois ou ils ont mange
			if (get_time() - last_meal > data->tt_die) //On compare cela avant l'horaire actuelle et le temps qu'ils prennent a mourir si ils ne mangent pas (donne par l'utilisateur)
			{
				safe_write(&data->philos[i], "died"); //Si on rentre dans ce block, c'est donc qu'un philo est mort (RIP)
				set_bool(&data->end_lock, &data->end, true); //Philo mort --> Arret de la simulation, mise a jour de la variable "end" (checkee par le monitor et chaque philos)
				break ;
			}
		}
		if (data->end == true) //Si jamais la fonction est finie, par besoin de checker la suite
			break ;
		if (data->must_eat != -1 && check_all_ate(data) == true) //Ici on check l'argument optionnel
		{
			set_bool(&data->end_lock, &data->end, true);
			break ;
		}
		//Les deux conditions de fin de simulation on ete checkees (philo mort OU tous les philo ont mange X fois), aucune des deux n'est atteintes, on continue donc la boucle jusqu'a qu'une des deux soit atteinte
	}
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (get_bool(&data->end_lock, &data->end) == false) //Encore une fois, un check pour verifier que la simulation n'est pas terminee
	{
		pthread_mutex_lock(philo->first_fork); //Lock de la premiere fourchette
		safe_write(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork); //Lock de la deuxieme fourchette
		safe_write(philo, "has taken a fork");
		set_long(&data->time_lock, &philo->last_meal, get_time()); //Puisque les deux fourchettes sont attrapees par le philo (et donc que les mutex sont lock), le philo peut manger. On met donc a jour la variable stockant le dernier horaire auxquel il a mange
		pthread_mutex_lock(&data->must_eat_lock);
		philo->must_eat_n += 1; //Incrementation du nombre de fois ou il a mange (gestion de l'argument optionnel)
		pthread_mutex_unlock(&data->must_eat_lock);
		safe_write(philo, "is eating");
		precise_sleep(data->tt_eat); //On attends le temps qu'il mange
		pthread_mutex_unlock(philo->first_fork); //Le philo a finit de manger, on unlock donc les deux forks (mutexs)
		pthread_mutex_unlock(philo->second_fork);
	}
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (get_bool(&data->start_lock, &data->start) == false) //Tant que la variable start n'est pas mise a true (dans la fonction parent de celle ci), on attend (que tous les threads soient crees)
		;
	set_long(&data->time_lock, &philo->last_meal, get_time()); //top depard //La simulation a demarre, on donne aux philos l'horaire de debut de simulation
	if (data->nb_philo == 1)
	{
		lone_philo(data); //Cas ou le programme est lance avec un seul philo (edge case)
		return (NULL);
	}
	if (philo->id % 2) //On fait sleep de 60ms les philos impairs, afin de regler des problemes de synchronisation. Si on ne fait pas ca, l'entierete des philos va attraper une fourchette, menant a un deadlock car toute les fourchettes sont prises.
		precise_sleep(60);
	while (get_bool(&data->end_lock, &data->end) == false) //Tant que la variable end est a false, cela veut dire que la routine des philos doit continuer, c'est notre boucle principale pour les philos, la ou ils vont manger, dormir et penser.
	{ //Cette variable end sera mise a true par la fonction monitor quand il detecte qu'un philo est mort (ou argument optionnel)

		//Eat, sleep, think, repeat
		philo_eat(philo);
		safe_write(philo, "is sleeping");
		precise_sleep(data->tt_sleep); //On attend le temps qu'il dorme
		safe_write(philo, "is thinking"); //Le philo est maintenant en attente de recuperer sa premiere fork
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo) //On loop a travers notre tableau de philos pour lancer les threads, et on leur donne leur fonction de routine (ils l'executeront en boucle tant qu'on ne join pas les threads)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (printf("Error while creating a thread\n"));
	}
	set_long(&data->time_lock, &data->start_time, get_time()); //Apres la creation de tous les threads, on utilise la fonction get_time pour attribuer a la variable start_time de ma structure data l'horaire de demarrage de la simulation
	set_bool(&data->start_lock, &data->start, true); //On peux maintenant mettre la variable start a true, afin que les fonction routine de nos philos puisse commencer la simulation (si on ne fait pas ca, le premier philo commencerait a manger, prendre des forks etc... Alors que tous les threads n'ont meme pas encore ete crees)
	monitor(data); //Lancement de la fonction monitor, qui va loop tant que la simulation est toujours en cours. Elle est responsable de la verification des philos morts, ainsi que de la gestion de l'argument optionnel ([number_of_times_each_philosopher_must_eat])
	i = -1;
	while (++i < data->nb_philo) //On loop a travers notre tableau de philos pour join les threads et donc arreter leur execution
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("Error while joining a thread\n"));
	}
	return (0);
}

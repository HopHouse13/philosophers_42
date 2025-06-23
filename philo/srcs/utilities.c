/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:57:07 by pab               #+#    #+#             */
/*   Updated: 2025/06/23 18:36:36 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_currentt(t_data *data)
{
	return (ft_get_time() - data->time);
}

void	ft_safe_write(t_philo *philo, pthread_mutex_t *write_lock, char *str)
{
	pthread_mutex_lock(write_lock);
	if (/* ft_get_bool(&philo->data->end_lock, &philo->data->end) */ philo->data->end == false)
		printf("%ld %d %s\n", ft_currentt(philo->data), philo->id, str);
	pthread_mutex_unlock(write_lock);
}

// Fonction pour faire un usleep precis.
// Elle se base sur ft_get_time qui se base sur gettimeofday qui est fiable.
// Principe : une boucle qui tourne et teste sa condition de sortie a une
// frequence determinee en fonction du nombre de philo pour alleger le CPU.
// (resume: frequence de check en fonction du nb_philo; plus il y en a, plus la
// frequence basse)
// la condition : si le temps passe entre l'initialisation de "start_time"
// est inferieur a "waiting_time" (duree que l'on veut attendre)
// exemple:
// on veut attendre 15
// start_time 40
// condition de boucle testee toutes les 5:
// test a 40 -> (40 - 40)0 < 15 ? oui
// test a 45 -> (45 - 40)5 < 15 ? oui
// test a 50 -> (50 - 40)10 < 15 ? oui
// test a 55 -> (55 - 40)15 < 15 ? non
// sortie de la boucle
void	ft_precise_waiting(t_data *data, long waiting_time)
{
	int		delay;
	long	start_time;
	
	if (data->nb_philo < 4)
		delay = 50;
	else if (data->nb_philo < 6)
		delay = 100;
	else if (data->nb_philo < 200)
		delay = 500;
	else
		delay = 1000;
	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < waiting_time)
		usleep(delay);
}

// La fonction gettimeofday() manipule une struct de deux VAR -> tv_sec(sec)
// et tv_usec(microsec). On obtient le nbr de sec et le nbr de microsec depuis
// le 1er janvier 1970. (tout le monde se cale sur ce timing)
// ON veut foncitonner en milliseconde, il faut donc convertir le retour en ms
// Pour les sec *1000 -> ms et les microsec /1000 -> ms et on additionne tout.
long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (printf("error with the function gettimeofday()\n"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// premiere boucle : on avance avec un "isspace"
// deuxieme boucle : on convertie tant c'est un chiffre
long	ft_atoi(const char *str)
{
	int		i;
	long	resultat;

	i = 0;
	resultat = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		resultat = resultat * 10 + (str[i++] - 48);
	return (resultat);
}

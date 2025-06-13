/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:07:51 by pab               #+#    #+#             */
/*   Updated: 2025/06/13 16:54:46 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct s_philo
{
	int				id;
	in
}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	int				nb_meal;
	t_philo			*philos;
	pthread_mutex_t *forks;
}					t_data;



#endif
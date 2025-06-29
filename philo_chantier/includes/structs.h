/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:07:51 by pab               #+#    #+#             */
/*   Updated: 2025/06/26 19:34:21 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long			last_meal;
	bool			ifinished;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}				t_philo;

typedef struct s_data
{	
	int				nb_philo;
	int				must_eat;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			tt_think;
	long			time;
	bool			end;

	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	meat_lock;
}					t_data;

#endif
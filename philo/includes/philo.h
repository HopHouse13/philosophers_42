/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/06/27 16:17:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/// STD_HEADERS ///
# include <stdio.h>					// printf
# include <stdbool.h>				// boolien
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>				// exit ; getenv ; malloc
# include <unistd.h>				// usleep
# include <sys/time.h>				// gestion du temps

/// HEADERS ///
# include "./structs.h"
# include "./font_style.h"

/// MAIN ///
int		main(int argc, char **argv);

/// PARSING ///
bool	ft_max_philo(char **argv);
bool	ft_sixty_ms(char **argv);
bool	ft_limit_int_max(char **argv);
bool	ft_only_digits(char **argv);
bool	ft_parsing(int argc, char **argv);

/// INIT_DATA ///
void	ft_init_philo(t_data *data);
bool	ft_init_mutex(t_data *data);
bool	ft_init_tabs(t_data *data);
void	ft_init_data(t_data *data, char **argv);
bool	ft_initialisation(t_data *data, char **argv);

/// SYNC_VALUES ///
void	ft_set_bool(pthread_mutex_t	*lock, bool	*value, bool update);
bool	ft_get_bool(pthread_mutex_t *lock, bool *value);
void	ft_set_long(pthread_mutex_t	*lock, long	*value, long update);
long	ft_get_long(pthread_mutex_t *lock, long *value);

/// SIMULATION ///
bool	ft_simulation(t_data *data);

/// ACTIONS ///
void	ft_eat(t_data *data, t_philo *philo);
void	ft_sleep(t_data *data, t_philo *philo);
void	ft_think(t_data *data, t_philo *philo);

/// FREE ///
void	ft_free(t_data *data);

/// UTILITIES ///
void	*ft_only_one(t_philo *philo);
void	ft_safe_write(t_philo *phil, pthread_mutex_t *wlock, char *str);
void	ft_precise_waiting(t_data *data, long waiting_time);
long	get_time(void);
long	ft_atoi(const char *str);

#endif
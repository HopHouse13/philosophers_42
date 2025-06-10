/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 16:31:24 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/// STD_HEADERS ///
# include <stdio.h>             // printf
# include <stdbool.h>           	// boolien
# include <limits.h>
# include <pthread.h>
// # include <unistd.h>				// get
// # include <errno.h>             // liste des erreurs errno.
// # include <readline/history.h>  // gere l'historique des commandes (non vide)
// # include <readline/readline.h> // declare la fonction readline.
// # include <stdlib.h>            // exit ; getenv ;
// # include <sys/errno.h>         // meilleur portabilite avec cette librairie.
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <string.h>
// # include <fcntl.h>				// open;

/// HEADERS ///
# include "./structs.h"
# include "./font_style.h"

/// MAIN ///
int		main(int argc, char **argv);

/// PARSING ///
bool	ft_limit_int_max(char **argv);
bool	ft_only_digits(char **argv);
bool	ft_parsing(int argc, char **argv);

/// INIT_DATA ///
bool	ft_init_all(t_data *data, char **argv);

/// SIMULATION ///
bool	ft_simulation(t_data *data);

/// FREE ///
void	ft_free(t_data *data);

/// UTILITIES ///
int		ft_atoi(const char *str);

#endif
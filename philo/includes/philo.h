/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/06/06 22:43:12 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/// STD_HEADERS ///
// # include <unistd.h>				// get
// # include <errno.h>             // liste des erreurs errno.
// # include <readline/history.h>  // gere l'historique des commandes (non vide)
// # include <readline/readline.h> // declare la fonction readline.
# include <stdbool.h>           	// boolien
// # include <stdio.h>             // printf (pour la phase de dev.); dprintf
// # include <stdlib.h>            // exit ; getenv ;
// # include <sys/errno.h>         // meilleur portabilite avec cette librairie.
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <string.h>
// # include <fcntl.h>				// open;
# include <pthread.h>

/// HEADERS ///
# include "./structs.h"
# include "./font_style.h"
# include "./libft/includes/libft.h"

/// MAIN ///
int		main(int argc, char **argv);

/// PARSING ///
bool	ft_limit_int_max(char **argv);
bool	ft_only_char(char **argv);
bool	ft_parsing(int argc, char **argv);

#endif
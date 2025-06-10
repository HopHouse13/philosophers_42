/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:44 by pbret             #+#    #+#             */
/*   Updated: 2025/06/10 19:32:19 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_limit_int_max(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) > INT_MAX)
			return (false);
	}
	return (true);
}

bool	ft_only_digits(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9') // isdigit
				return (false);
		}
	}
	return (true);
}

bool	ft_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf(RED"nombre d'argument invalide\n"RESET));
	if (!ft_only_digits(argv))
		return (printf(RED"caractere invalide\n"RESET));
	if (!ft_limit_int_max(argv))
		return (printf(RED"limite de valeur depassee\n"RESET));
	return (false);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:44 by pbret             #+#    #+#             */
/*   Updated: 2025/06/06 16:09:39 by pab              ###   ########.fr       */
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

bool	ft_only_char(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (false);
		}
	}
	return (true);
}

bool	ft_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);
	if (!ft_only_char(argv))
		return (false);
	if (!ft_limit_int_max(argv))
		return (false);
	return (true);
}
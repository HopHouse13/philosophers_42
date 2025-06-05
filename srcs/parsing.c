/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:44 by pbret             #+#    #+#             */
/*   Updated: 2025/06/05 19:18:28 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	// if (ft_limits_int(argv))
	// 	return (false);
	return (true);
}
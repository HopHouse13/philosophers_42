/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:44 by pbret             #+#    #+#             */
/*   Updated: 2025/06/25 20:39:04 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_max_philo(char **argv)
{
	if (argv[1] && ft_atoi(argv[1]) > 200)
		return (false);
	return (true);
}

bool	ft_sixty_ms(char **argv)
{
	int	i;

	i = 1;
	while (argv[++i] && i <= 4)
	{
		if (ft_atoi(argv[i]) < 60)
			return (false);
	}
	return (true);
}

bool	ft_limit_int_max(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 0)
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
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
		}
	}
	return (true);
}

bool	ft_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf(RED"invalid number of arguments\n"RESET));
	if (!ft_only_digits(argv))
		return (printf(RED"Invalid character: only digits are allowed\n"RESET));
	if (!ft_limit_int_max(argv))
		return (printf(RED"Integer value exceeds the limits\n"RESET));
	if (!ft_sixty_ms(argv))
		return (printf(RED"Time value < 60 millisecond\n"RESET));
	if (!ft_max_philo(argv))
		return (printf(RED"Maximum number of philosophers is 200\n"RESET));
	return (false);
}

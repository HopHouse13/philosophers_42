/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:12:39 by pbret             #+#    #+#             */
/*   Updated: 2025/06/17 21:11:08 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (ft_parsing(argc, argv))
		return (1);
	if (ft_initialisation(&data, argv))
		return (2);
	if (ft_simulation(&data))
		{printf(RED"SIMULATION_INVALIDE\n"RESET); return (3);}
	ft_free(&data);
	printf(GREEN"FIN_DE_SIMULATION\n"RESET);
	return (0);
}	
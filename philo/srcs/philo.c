/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:12:39 by pbret             #+#    #+#             */
/*   Updated: 2025/06/10 19:31:15 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	//t_data data;

	if (ft_parsing(argc, argv))
		return (1);
	// if (!ft_init_all(&data, argv))
	// 	{printf(RED"INIT_INVALIDE\n"RESET); return (2);}
	// if (!ft_simulation(&data))
	// 	{printf(RED"SIMULATION_INVALIDE\n"RESET); return (3);}
	// ft_free(&data);
	printf(GREEN"FIN_DE_SIMULATION\n"RESET);
	return (0);
}
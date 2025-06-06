/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:12:39 by pbret             #+#    #+#             */
/*   Updated: 2025/06/05 19:02:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	if (ft_parsing(argc, argv))
		printf("SUCCESSFULL\n");
	else
		printf("PAS OUF TON TRUC\n");
	return (0);
}
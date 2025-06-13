/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:57:07 by pab               #+#    #+#             */
/*   Updated: 2025/06/13 09:45:18 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

long	ft_atoi(const char *str)
{
	int		i;
	long	resultat;

	i = 0;
	resultat = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32) // isspace
		i++;
	while (str[i] >= 48 && str[i] <= 57) // isdigit
		resultat = resultat * 10 + (str[i++] - 48);
	return (resultat);
}

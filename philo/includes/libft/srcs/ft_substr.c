/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:22 by pbret             #+#    #+#             */
/*   Updated: 2025/03/11 21:49:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// dupliquer une une partie de la src dans une sous chaine
// si l'indice (start) est > ou = a la len de src
// -> return une chaine vide (strdup)
// si longueur de la sous chaine est > (len de src)-(l'indice de depart(start))
// -> tronquer len pour pas quelle depasse src
// s_new = ft_calloc et duplique avec while (pour pas depasser src)
// et if (pour pas depasser len)

char	*ft_substr(char const *s_src, int start, int len)
{
	char	*s_new;
	int		j;

	if (!s_src)
		return (NULL);
	if (start >= ft_strlen(s_src))
	{
		s_new = ft_calloc(1, sizeof(char));
		if (!s_new)
			return (NULL);
		return (s_new);
	}
	if (len > ft_strlen(s_src) - start)
		len = ft_strlen(s_src) - start;
	s_new = ft_calloc((len + 1), sizeof(char));
	if (!s_new)
		return (NULL);
	j = 0;
	while (j < len && s_src[start])
		s_new[j++] = s_src[start++];
	s_new[j] = '\0';
	return (s_new);
}

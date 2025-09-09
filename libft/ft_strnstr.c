/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:04:42 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/24 14:03:32 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	if (!s2[0] || len <= 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && len > 0)
	{
		while (i + j < len && s1[i + j] == s2[j])
		{
			if (s2[j + 1] == 0)
				return ((char *)&s1[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

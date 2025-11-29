/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:21:57 by lucas             #+#    #+#             */
/*   Updated: 2025/02/17 11:14:19 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *dest, const char *src)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!src)
		return (dest);
	if (!dest)
		return (ft_strdup(src));
	len = ft_strlen(dest) + ft_strlen(src);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (free(dest), NULL);
	i = -1;
	while (dest[++i])
		res[i] = dest[i];
	j = 0;
	while (src[j])
	{
		res[i] = src[j];
		i++;
		j++;
	}
	return (free(dest), res);
}

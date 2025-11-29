/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:29:51 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/01/01 21:05:37 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcrop(const char *str, int c)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = str[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

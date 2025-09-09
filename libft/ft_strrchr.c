/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:04:45 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/24 11:13:20 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	int				res;

	i = 0;
	res = -1;
	if (c == 0 && s[ft_strlen(s)] == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == c)
		{
			res = i;
		}
		i++;
	}
	if (res != -1)
		return ((char *)&s[res]);
	return (0);
}

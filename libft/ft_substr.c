/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lmarcucc42lyon.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:00 by lmarcucc          #+#    #+#             */
/*   Updated: 2024/11/09 11:01:20 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	total_len;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = ft_calloc(1, sizeof(char));
		return (str);
	}
	total_len = ft_strlen(&s[start]);
	if (len < total_len)
		total_len = len;
	str = ft_calloc(total_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
		if (i >= start && ++j < len)
			str[j] = s[i];
	return (str);
}

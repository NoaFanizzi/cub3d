/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:03:56 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/02/17 11:33:57 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	copy(char **tab, const char *s, int sep)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep)
		{
			tab[j] = ft_strcrop(&s[i], sep);
			if (!tab[j])
				return (false);
			j++;
			while (s[i] != sep && s[i])
				i++;
		}
		else
			i++;
	}
	return (true);
}

char	**ft_split(const char *str, int c)
{
	int		words;
	char	**res;

	if (!str)
		return (NULL);
	words = ft_count_words(str, c);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!copy(res, str, c))
		return (ft_free_split(res), NULL);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:42:57 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:43:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_suffix_correct(char *str, char *suffix)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i + 1])
		i++;
	while (j < 4)
	{
		if (str[i] != suffix[j])
			return (1);
		i--;
		j++;
	}
	return (0);
}

int	is_map_suffix_correct(t_config *config, char *suffix)
{
	if ((is_suffix_correct(config->tex_no, suffix) != 0)
		|| (is_suffix_correct(config->tex_so, suffix) != 0)
		|| (is_suffix_correct(config->tex_we, suffix) != 0)
		|| (is_suffix_correct(config->tex_ea, suffix) != 0))
		return (1);
	return (0);
}

int	is_only_space(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

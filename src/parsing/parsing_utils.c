/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:45:38 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:43:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	replace_char(char ***map, char old, char nw, t_config *config)
{
	size_t	i;
	size_t	j;

	i = 0;
	(void)config;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == old)
				(*map)[i][j] = nw;
			j++;
		}
		i++;
	}
}

void	get_tab_length(char ***tab, size_t *length)
{
	size_t	i;

	i = 0;
	*length = 0;
	if (!(*tab))
		return ;
	while ((*tab)[i])
	{
		*length += 1;
		i++;
	}
}

int	get_last_line_pos(char ***map)
{
	size_t	i;

	i = 0;
	while ((*map)[i + 1])
		i++;
	return (i);
}

int	get_last_line_length(char ***map)
{
	size_t	pos;
	size_t	length;

	length = 0;
	pos = get_last_line_pos(map);
	length = ft_strlen((*map)[pos]);
	return (length);
}

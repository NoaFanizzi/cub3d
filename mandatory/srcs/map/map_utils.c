/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:38:48 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/06 19:39:28 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_size(t_size *size, char ***map)
{
	size->x = 0;
	if (!(*map))
	{
		size->x = 0;
		return ;
	}
	while ((*map)[size->x])
		size->x += 1;
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
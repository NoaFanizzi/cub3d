/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:38:48 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 08:44:00 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_texture_data(t_texture *texture)
{
	printf("NO = %s\n", texture->NO);
	printf("SO = %s\n", texture->SO);
	printf("WE = %s\n", texture->WE);
	printf("EA = %s\n", texture->EA);
}

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

void	replace_char(char ***map, char old, char new)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == old)
				(*map)[i][j] = new;
			j++;
		}
		i++;
	}
}

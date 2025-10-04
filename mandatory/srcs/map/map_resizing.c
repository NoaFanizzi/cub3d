/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_resizing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:30:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 08:34:13 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_last_line(char ***map)
{
	size_t	length;
	char	*line_full_x;
	char	**new_map;
	char	**old_map;

	length = get_last_line_length(map);
	line_full_x = ft_calloc(length + 1, sizeof(char));
	if (!line_full_x)
		return ;
	load_delimitation_line(&line_full_x, length);
	old_map = *map;
	resize_map(map, &new_map, &line_full_x, 1);
	if (new_map)
	{
		if (old_map)
			free_tab(&old_map);
		*map = new_map;
	}
	free(line_full_x);
}

void	load_delimitation_line(char **trimmed_map, size_t length)
{
	size_t	i;

	i = 0;
	(*trimmed_map)[0] = 'X';
	while (i < length)
	{
		(*trimmed_map)[i] = 'X';
		i++;
	}
}

void	resize_map(char ***map, char ***new_map, char **temp, int is_last)
{
	size_t	length;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	get_tab_length(map, &length);
	*new_map = ft_calloc(length + 2, sizeof(char *)); // + 1 pour la nouvelle ligne, + 1 pour le NULL de fin
	while (i < length)
	{
		(*new_map)[i] = ft_strdup((*map)[i]);
		i++;
	}
	length = ft_strlen(*temp);
	(*new_map)[i] = ft_calloc(length + 3, sizeof(char)); // + 1 pour le null byte, + 2 pour le 1er et le dernier X
	(*new_map)[i][0] = 'X';
	while ((*temp)[j])
	{
		if (is_last == 1 && !((*temp)[j + 1]))
			break ;
		(*new_map)[i][j + 1] = (*temp)[j];
		j++;
	}
	j++;
	if (is_last == 0)
		(*new_map)[i][j] = 'X';
}

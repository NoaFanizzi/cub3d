/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:02:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/06 19:39:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	add_last_line(char ***map)
{
	size_t	length;
	char	*line_full_X;
	char	**new_map;
	char	**old_map;

	length = get_last_line_length(map);
	line_full_X = ft_calloc(length + 1, sizeof(char));
	if (!line_full_X)
		return;
		
	load_delimitation_line(&line_full_X, length);
	old_map = *map;
	resize_map(map, &new_map, &line_full_X, 1);
	
	if (new_map)
	{
		if (old_map)
			free_tab(&old_map);
		*map = new_map;
	}
	free(line_full_X);
}

int	update_map(char ***map, char **temp)
{
	char	**new_map;
	char	*trimmed_line;
	char	*line_full_X;

	if (!*temp)
	{
		add_last_line(map);
		return (0);
	}
	trimmed_line = ft_strtrim(*temp, "\n");
	if (*map)
	{
		resize_map(map, &new_map, &trimmed_line, 0);
	}
	else
	{
		line_full_X = ft_calloc(ft_strlen(trimmed_line) + 3, sizeof(char));
		load_delimitation_line(&line_full_X, ft_strlen(trimmed_line));
		resize_map(map, &temp, &line_full_X, 0);
		free(line_full_X);
		resize_map(&temp, &new_map, &trimmed_line, 0);
		if (*temp)
			free_tab(&temp);
	}
	if (*map)
		free_tab(map);
	*map = new_map;
	ft_wipe(&trimmed_line);
	return (0);
}

char	**get_map(char **argv)
{
	int		fd;
	char	*temp;
	char	**map;

	map = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		temp = get_next_line(fd);
		update_map(&map, &temp);
		if (!temp)
			break ;
		free(temp);
	}
	close(fd);
	return (map);
}

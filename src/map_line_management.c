/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:47:06 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:02:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_and_add_texture(char *temp, const char *prefix, char **dest)
{
	char	*trimmed_path;

	if (ft_strncmp(temp, prefix, 3) != 0)
	{
		ft_wipe(&temp);
		return (1);
	}
	if (*dest)
	{
		ft_putstr_fd("Error: Duplicate texture definition\n", 2);
		ft_wipe(&temp);
		return (1);
	}
	trimmed_path = ft_strtrim(&temp[3], " \t\n\v\f\r"); // PROTECTED
	ft_wipe(&temp);
	if (!trimmed_path || ft_strlen(trimmed_path) == 0)
	{
		if (trimmed_path)
			free(trimmed_path);
		return (1);
	}
	*dest = trimmed_path;
	return (0);
}

int	init_first_lines(char ***new_map, char *line)
{
	char	*border;
	char	**temp_map;
	char	**dummy;

	dummy = NULL;
	border = ft_calloc(ft_strlen(line) + 3, sizeof(char));
	if (!border)
		return (1);
	load_delimitation_line(&border, ft_strlen(line));
	if (resize_map(&dummy, &temp_map, &border, 0))
	{
		free(border);
		return (1);
	}
	free(border);
	if (resize_map(&temp_map, new_map, &line, 0))
	{
		free_tab(&temp_map);
		return (1);
	}
	free_tab(&temp_map);
	return (0);
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
	char	*line_full_x;
	char	**new_map;
	char	**old_map;

	length = get_last_line_length(map);
	line_full_x = ft_calloc(length + 1, sizeof(char));
	if (!line_full_x)
		return ;
	load_delimitation_line(&line_full_x, length);
	old_map = *map;
	if (resize_map(map, &new_map, &line_full_x, 1) == 0)
		// FIXED: Check return value
	{
		if (old_map)
			free_tab(&old_map);
		*map = new_map;
	}
	free(line_full_x);
}

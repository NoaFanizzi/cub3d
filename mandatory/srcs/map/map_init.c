/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:02:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 08:50:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "clean.h"

int	update_map(char ***map, char **temp)
{
	char	**new_map;
	char	*trimmed_line;
	char	*line_full_x;

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
		line_full_x = ft_calloc(ft_strlen(trimmed_line) + 3, sizeof(char));
		load_delimitation_line(&line_full_x, ft_strlen(trimmed_line));
		resize_map(map, &temp, &line_full_x, 0);
		free(line_full_x);
		resize_map(&temp, &new_map, &trimmed_line, 0);
		if (*temp)
			free_tab(&temp);
	}
	if (*map)
		free_tab(map);
	*map = new_map;
	wipe(&trimmed_line);
	return (0);
}

char	**get_map(char **argv)
{
	int		fd;
	char	*temp;
	char	**map;
	t_texture texture;

	map = NULL;
	texture.NO = NULL;
	texture.SO = NULL;
	texture.WE = NULL;
	texture.EA = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (get_textures(fd, &texture) == 1)
		return(NULL);
	if(is_suffix_correct(argv[1], "mpx.") == 1)
	{
		clean_texture(&texture);
		return(NULL);
	}
	display_texture_data(&texture);
	while (1)
	{
		temp = get_next_line(fd);
		update_map(&map, &temp);
		if (!temp)
			break ;
		free(temp);
	}
	close(fd);
	replace_char(&map, ' ', 'X');
	return (map);
}

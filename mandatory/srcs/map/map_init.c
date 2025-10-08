/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:02:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 14:01:17 by nofanizz         ###   ########.fr       */
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
		printf("LAAAAA\n");
		add_last_line(map);
		return (0);
	}
	if(!(*temp)[0])
		return(0);
	trimmed_line = ft_strtrim(*temp, "\n");
	if (*map)
	{
		resize_map(map, &new_map, &trimmed_line, 0);
	}
	else
	{
		printf("ICI\n");
		line_full_x = ft_calloc(ft_strlen(trimmed_line) + 3, sizeof(char));
		printf("trimmed line = %s\n", trimmed_line);
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

int	is_map_suffix_correct(t_data *data, char *suffix)
{
	if((is_suffix_correct(data->texture[NO].path, suffix) != 0)
	||(is_suffix_correct(data->texture[SO].path, suffix) != 0)
	||(is_suffix_correct(data->texture[WE].path, suffix) != 0)
	||(is_suffix_correct(data->texture[EA].path, suffix) != 0))
		return(1);
	return(0);
}

int	is_only_space(char *str)
{
	size_t	i;

	i = 0;
	if(!str)
		return(1);
	while(str[i])
	{
		if(ft_isspace(str[i]) == 0)
			return(1);
		i++;
	}
	return(0);
}

char	**get_map(char **argv, t_data *data)
{
	int		fd;
	char	*temp;
	char	**map;

	map = NULL;
	data->texture[NO].path = NULL;
	data->texture[SO].path = NULL;
	data->texture[WE].path = NULL;
	data->texture[EA].path = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (parse_textures(fd, data) == 1)
		return(NULL);
	display_texture_data(data);
	if(is_map_suffix_correct(data, "mpx.") == 1)
	{
		clean_texture(data);
		return(NULL);
	}
	printf("----------------------map just before GNL----------------------\n\n\n");
	display_tab(map);
	printf("------------------------------end------------------------------\n\n\n\n\n");
	display_tab(map);
	while (1)
	{
		temp = get_next_line(fd);
		if(is_only_space(temp) == 0)
		{
			free(temp);
			continue;
		}
		printf("temp = %s\n", temp);
		update_map(&map, &temp);
		printf("-----------------------display_map_in_gnl-------------------------\n\n\n");
		display_tab(map);
		printf("-----------------------END-----------------------\n\n\n");
		if (!temp)
			break ;
		free(temp);
	}
	close(fd);
	replace_char(&map, ' ', 'X');
	return (map);
}

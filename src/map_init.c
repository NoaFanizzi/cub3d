/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:01:53 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/29 17:13:51 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	replace_char(char ***map, char old, char new, t_config *config)
{
	size_t	i;
	size_t	j;
	//size_t tp_positionned;

	i = 0;
	(void)config;
	//tp_positionned = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			//if((*map)[i][j] == '1' && tp_positionned == 0)
			// if((*map)[i][j] == '1')
			// {
			// 	data->tp_pos.y = i;
			// 	data->tp_pos.x = j;
			// }
			if ((*map)[i][j] == old)
				(*map)[i][j] = new;
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
	if(!(*temp)[0])
		return(0);
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
	*map = new_map;
	ft_wipe(&trimmed_line);
	return (0);
}

int	check_and_add_texture(char *temp, const char *prefix, char **dest)
{
	if (ft_strncmp(temp, prefix, 3) != 0)
	{
		ft_wipe(&temp);
		return (1);
	}
	if (ft_strlen(temp) <= 3)
	{
		ft_wipe(&temp);
		return (1);
	}
	*dest = ft_strdup(&temp[3]);
	ft_wipe(&temp);
	return (0);
}

char	**get_map(char **argv, t_config *config)
{
	int		fd;
	char	*temp;
	char	**map;
	
	map = NULL;
	config->tex_no = NULL;
	config->tex_so = NULL;
	config->tex_we = NULL;
	config->tex_ea = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (parse_textures(fd, config) == 1)
		return(NULL);
	//display_texture_data(data);
	if(is_map_suffix_correct(config, "mpx.") == 1)
	{
		clean_texture(config);
		return(NULL);
	}
	//display_tab(map);
	//display_tab(map);
	while (1)
	{
		temp = get_next_line(fd);
		if(is_only_space(temp) == 0)
		{
			free(temp);
			continue;
		}
		update_map(&map, &temp);
		//display_tab(map);
		if (!temp)
			break ;
		free(temp);
	}
	close(fd);
	replace_char(&map, ' ', 'X', config);
	return (map);
}
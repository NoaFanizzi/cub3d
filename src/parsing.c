/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:00:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 14:31:02 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_validity(char **map)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '0' && map[i][j] != '1') && (map[i][j] != 'N'
					&& map[i][j] != 'S') && (map[i][j] != 'E'
					&& map[i][j] != 'W' && map[i][j] != 'X'))
				return (1);
			if ((map[i][j] == 'N' || map[i][j] == 'S') || (map[i][j] == 'E'
					|| map[i][j] == 'W'))
				count++;
			if (count > 1)
				return (1);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

static int	parse_single_texture(int fd, const char *prefix, char **dest)
{
	char	*temp;

	temp = get_next_line(fd);
	if (!temp)
		return (1);
	while (is_only_space(temp) == 0)
	{
		free(temp);
		temp = get_next_line(fd);
		if (!temp)
			return (1);
	}
	if (check_and_add_texture(temp, prefix, dest))
		return (1);
	remove_last_char(*dest);
	return (0);
}

int	parse_textures(int fd, t_config *config)
{
	if (parse_single_texture(fd, "NO ", &config->tex_no))
		return (1);
	if (parse_single_texture(fd, "SO ", &config->tex_so))
	{
		ft_wipe(&config->tex_no);
		return (1);
	}
	if (parse_single_texture(fd, "WE ", &config->tex_we))
	{
		ft_wipe(&config->tex_no);
		ft_wipe(&config->tex_so);
		return (1);
	}
	if (parse_single_texture(fd, "EA ", &config->tex_ea))
	{
		ft_wipe(&config->tex_no);
		ft_wipe(&config->tex_so);
		ft_wipe(&config->tex_we);
		return (1);
	}
	return (0);
}

int	check_border(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' 
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
					return (1);
				if (map[i][j - 1] == 'X' || map[i][j + 1] == 'X'
					|| map[i - 1][j] == 'X' || map[i + 1][j] == 'X')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_parser(int argc, char **argv, char ***map, t_config *config)
{
	*map = NULL;
	if (argc != 2)
		return (1);
	if (is_suffix_correct(argv[1], "buc.") == 1)
		return (1);
	*map = get_map(argv, config);
	if (!*map)
		return (1);
	if (check_border(*map) == 1)
	{
		free_tab(map);
		clean_texture(config);
		return (1);
	}
	if (check_validity(*map) == 1)
	{
		free_tab(map);
		clean_texture(config);
		return (1);
	}
	replace_char(map, 'X', '1', config);
	return (0);
}

int parse_config_line(char *line, t_config *config)
{
    int i = 0;

    while (line[i] && ft_isspace(line[i]))
        i++;
    if (!line[i])
        return (2);

    if (!ft_strncmp(&line[i], "NO ", 3))
        return (check_and_add_texture(ft_strdup(&line[i]), "NO ", &config->tex_no));
    else if (!ft_strncmp(&line[i], "SO ", 3))
        return (check_and_add_texture(ft_strdup(&line[i]), "SO ", &config->tex_so));
    else if (!ft_strncmp(&line[i], "WE ", 3))
        return (check_and_add_texture(ft_strdup(&line[i]), "WE ", &config->tex_we));
    else if (!ft_strncmp(&line[i], "EA ", 3))
        return (check_and_add_texture(ft_strdup(&line[i]), "EA ", &config->tex_ea));
    else if (!ft_strncmp(&line[i], "F ", 2))
        return (parse_color_line(&line[i], 'F', config->floor));
    else if (!ft_strncmp(&line[i], "C ", 2))
        return (parse_color_line(&line[i], 'C', config->ceiling));
        
    return (2);
}

int is_config_complete(t_config *config)
{
    if (!config->tex_no || !config->tex_so || !config->tex_we || !config->tex_ea)
        return (0);
    if (config->floor[0] == -1 || config->ceiling[0] == -1)
        return (0);
        
    return (1);
}

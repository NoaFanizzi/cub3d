/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:01:53 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 18:48:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	handle_map_error(char **line, char ***map, int fd)
{
	if (line && *line)
		free(*line);
	if (map && *map)
		free_tab(map);
	close(fd);
	return (1);
}

static int	handle_config_line(char *line, t_config *config, char ***map, int fd)
{
	int	config_res;

	config_res = parse_config_line(line, config);
	if (config_res == 0)
		free(line);
	else if (config_res == 1)
		return (handle_map_error(&line, map, fd));
	else
	{
		if (!is_config_complete(config))
			return (handle_map_error(&line, map, fd));
	}
	return (config_res);
}

static int	handle_map_line(char **line, int *map_started)
{
	if (is_only_space(*line) == 0)
	{
		free(*line);
		if (*map_started)
			*map_started = 2;
		return (1);
	}
	return (0);
}

static int	read_map_loop(int fd, t_config *config, char ***map)
{
	char	*line;
	int		map_started;
	int		res;

	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (handle_map_line(&line, &map_started))
			continue ;
		if (map_started == 2)
			return (handle_map_error(&line, map, fd), 0);
		res = handle_config_line(line, config, map, fd);
		if (res == 1)
			return (0);
		else if (res == 2)
		{
			map_started = 1;
			if (update_map(map, &line) != 0)
				return (handle_map_error(&line, map, fd), 0);
			free(line);
		}
	}
	return (1);
}

char	**get_map(char **argv, t_config *config)
{
	int		fd;
	char	**map;

	map = NULL;
	config->floor[0] = -1;
	config->ceiling[0] = -1;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!read_map_loop(fd, config, &map))
		return (NULL);
	close(fd);
	if (!map || !is_config_complete(config))
		return (NULL);
	replace_char(&map, ' ', 'X', config);
	return (map);
}

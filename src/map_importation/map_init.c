/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:01:53 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:41:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parsing.h"
#include "map.h"

static int	handle_config_line(char *line, t_config *config, char ***map,
		int fd)
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

static int	process_line(char **line, int *map_started, char ***map,
		t_config *config)
{
	int	res;

	if (handle_map_line(line, map_started))
		return (2);
	if (*map_started == 2)
	{
		handle_map_error(line, map, -1);
		return (0);
	}
	res = handle_config_line(*line, config, map, -1);
	if (res == 1)
		return (0);
	else if (res == 2)
		return (handle_map_case(line, map_started, map, -1));
	return (1);
}

static int	read_map_loop(int fd, t_config *config, char ***map)
{
	char	*line;
	int		map_started;
	int		result;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		result = process_line(&line, &map_started, map, config);
		if (result == 0)
		{
			close(fd);
			return (0);
		}
		if (result == 2)
		{
			line = get_next_line(fd);
			continue ;
		}
		line = get_next_line(fd);
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

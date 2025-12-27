/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:10:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:42:49 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	handle_map_error(char **line, char ***map, int fd)
{
	if (line && *line)
		free(*line);
	if (map && *map)
		free_tab(map);
	close(fd);
	return (1);
}

int	handle_map_case(char **line, int *map_started, char ***map, int fd)
{
	*map_started = 1;
	if (update_map(map, line) != 0)
	{
		handle_map_error(line, map, fd);
		return (0);
	}
	free(*line);
	return (1);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	validate_line_format(char *line, char identifier)
{
	if (line[0] != identifier || !ft_isspace(line[1]))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:27:41 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:44:55 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parsing.h"

static int	count_colors(char **colors)
{
	size_t	i;

	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
		return (1);
	return (0);
}

static int	validate_and_store_color(char *str, int *color_array, size_t index)
{
	int	val;

	if (!is_str_digit(str))
		return (1);
	val = ft_atoi(str);
	if (val < 0 || val > 255)
		return (1);
	color_array[index] = val;
	return (0);
}

static int	process_color_values(char **colors, int *color_array)
{
	size_t	i;

	i = 0;
	while (colors[i])
	{
		if (validate_and_store_color(colors[i], color_array, i))
			return (1);
		i++;
	}
	return (0);
}

int	parse_color_line(char *line, char identifier, int *color_array)
{
	char	**colors;
	int		error;

	if (validate_line_format(line, identifier))
		return (1);
	colors = ft_split(&line[2], ',');
	if (!colors)
		return (1);
	if (count_colors(colors))
	{
		free_tab((char ***)&colors);
		return (1);
	}
	error = process_color_values(colors, color_array);
	free_tab((char ***)&colors);
	return (error);
}

int	parse_colors(int fd, t_config *config)
{
	char	*temp;

	temp = get_next_line(fd); // PROTECTED
	while (is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	printf("Color line 1: %s", temp);
	if (!temp || parse_color_line(temp, 'F', config->floor))
		return (1);
	temp = get_next_line(fd); // PROTECTED
	while (is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	if (!temp || parse_color_line(temp, 'C', config->ceiling))
		return (1);
	return (0);
}

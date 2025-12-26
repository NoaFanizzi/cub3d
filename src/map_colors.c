/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:27:41 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 18:29:11 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int is_str_digit(char *str)
{
    int i = 0;

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

void	ft_display_colors(t_config *config)
{
	printf("Floor color: R=%d, G=%d, B=%d\n", config->floor[0], config->floor[1], config->floor[2]);
	printf("Ceiling color: R=%d, G=%d, B=%d\n", config->ceiling[0], config->ceiling[1], config->ceiling[2]);
}

int parse_color_line(char *line, char identifier, int *color_array)
{
    char    **colors;
    size_t  i;
    int     val;

    if (line[0] != identifier || !ft_isspace(line[1]))
        return (1);
    colors = ft_split(&line[2], ',');
    if (!colors)
        return (1);
    i = 0;
    while (colors[i])
        i++;
    if (i != 3)
    {
        free_tab((char ***)&colors);
        return (1);
    }
    i = 0;
    while (colors[i])
    {
        if (!is_str_digit(colors[i]))
        {
            free_tab((char ***)&colors);
            return (1);
        }
        val = ft_atoi(colors[i]);
        if (val < 0 || val > 255)
        {
            free_tab((char ***)&colors);
            return (1);
        }
        color_array[i] = val;
        i++;
    }
    free_tab((char ***)&colors);
    return (0);
}

int parse_colors(int fd, t_config *config)
{
	char	*temp;

	temp = get_next_line(fd); //PROTECTED
	while(is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	printf("Color line 1: %s", temp);
	if (!temp || parse_color_line(temp, 'F', config->floor))
		return (1);
	temp = get_next_line(fd); //PROTECTED
	while(is_only_space(temp) == 0)
	{
		ft_wipe(&temp);
		temp = get_next_line(fd);
	}
	if (!temp || parse_color_line(temp, 'C', config->ceiling))
		return (1);
	return (0);
}

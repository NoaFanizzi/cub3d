/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:00:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:32:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	parse_config_line(char *line, t_config *config)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (2);
	if (!ft_strncmp(&line[i], "NO ", 3))
		return (check_and_add_texture(ft_strdup(&line[i]), "NO ",
				&config->tex_no));
	else if (!ft_strncmp(&line[i], "SO ", 3))
		return (check_and_add_texture(ft_strdup(&line[i]), "SO ",
				&config->tex_so));
	else if (!ft_strncmp(&line[i], "WE ", 3))
		return (check_and_add_texture(ft_strdup(&line[i]), "WE ",
				&config->tex_we));
	else if (!ft_strncmp(&line[i], "EA ", 3))
		return (check_and_add_texture(ft_strdup(&line[i]), "EA ",
				&config->tex_ea));
	else if (!ft_strncmp(&line[i], "F ", 2))
		return (parse_color_line(&line[i], 'F', config->floor));
	else if (!ft_strncmp(&line[i], "C ", 2))
		return (parse_color_line(&line[i], 'C', config->ceiling));
	return (2);
}

int	is_config_complete(t_config *config)
{
	if (!config->tex_no || !config->tex_so || !config->tex_we
		|| !config->tex_ea)
		return (0);
	if (config->floor[0] == -1 || config->ceiling[0] == -1)
		return (0);
	return (1);
}

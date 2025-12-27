/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:31:38 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:32:14 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

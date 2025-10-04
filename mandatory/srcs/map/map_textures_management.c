/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:33:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 08:49:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_and_add_texture(char *temp, const char *prefix, char **dest)
{
	if (ft_strncmp(temp, prefix, 3) != 0)
	{
		free(temp);
		return (1);
	}
	if (ft_strlen(temp) <= 3)
	{
		free(temp);
		return (1);
	}
	*dest = ft_strdup(&temp[3]);
	free(temp);
	return (0);
}

int	get_textures(int fd, t_texture *texture)
{
	char	*temp;

	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "NO ", &texture->NO))
		return (1);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "SO ", &texture->SO))
		return (1);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "WE ", &texture->WE))
		return (1);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "EA ", &texture->EA))
		return (1);
	return (0);
}

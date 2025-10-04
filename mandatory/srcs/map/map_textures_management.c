/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:33:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 10:58:49 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_and_add_texture(char *temp, const char *prefix, char **dest)
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

// void    init_texture()
// {
//     int width;
//     int height;
    
//     data->textures[0].img = mlx_xpm_file_to_image(data->mlx, "textures/wall_north.xpm", &width, &height);
//     if (!data->textures[0].img) 
//         exit_error("Impossible de charger texture");
//     data->textures[0].addr = (int *)mlx_get_data_addr(data->textures[0].img, 
//         &data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);
//     data->textures[0].width = width;
//     data->textures[0].height = height;
// }


int	parse_textures(int fd, t_data *data)
{
	char	*temp;

	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "NO ", &data->texture[NO].path))
		return (1);
	remove_last_char(data->texture[NO].path);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "SO ", &data->texture[SO].path))
		return (1);
	remove_last_char(data->texture[SO].path);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "WE ", &data->texture[WE].path))
		return (1);
	remove_last_char(data->texture[WE].path);
	temp = get_next_line(fd);
	if (!temp || check_and_add_texture(temp, "EA ", &data->texture[EA].path))
		return (1);
	remove_last_char(data->texture[EA].path);
	return (0);
}

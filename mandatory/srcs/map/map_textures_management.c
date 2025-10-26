/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 08:33:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/26 11:52:16 by nofanizz         ###   ########.fr       */
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

void    init_texture(void *mlx_ptr, t_texture *texture, char *file_path)
{
    int width;
    int height;

    texture->img = mlx_xpm_file_to_image(mlx_ptr, file_path, &width, &height);
    if (!texture->img)
    {
        perror("Erreur chargement texture");
        exit(EXIT_FAILURE);
    }
    texture->addr = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
                                            &texture->line_length, &texture->endian);
    texture->width = width;
    texture->height = height;
}

t_texture	*select_texture(t_data *data, t_dda *dda, t_dda2 *dda2)
{
	if (dda2->side == 0)
	{
		if (dda->step_x > 0)
			return (&data->texture[EA]);
		else
			return (&data->texture[WE]);
	}
	else
	{
		if (dda2->step_y > 0)
			return (&data->texture[SO]);
		else
			return (&data->texture[NO]);
	}
}

void	init_tex_render(t_tex *tex, t_wall *wall)
{
	tex->step = 1.0 * tex->tex->height / wall->line_height;
	tex->tex_pos = (wall->draw_start - WINDOW_HEIGHT * 0.5
			+ wall->line_height * 0.5) * tex->step;
}

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

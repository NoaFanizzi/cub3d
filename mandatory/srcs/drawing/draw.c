/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:13:41 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 16:18:01 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tile_size(char **map)
{
	int	i;
	t_vec2 size;

	size = (t_vec2){0, 0};
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > size.x)
			size.x = (int)ft_strlen(map[i]);
		size.y = i + 1;
		i++;
	}
	printf("map size = [%d, %d]\n", size.x, size.y);
	if (size.x > size.y)
		return (WINDOW_WIDTH / size.x);
	return (WINDOW_HEIGHT / size.y);
}

t_vec2f	get_start_pos(t_data *data)
{
	int	i;
	int	j;
	t_vec2f	start_pos;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W' ||
				data->map[i][j] == 'S' || data->map[i][j] == 'E')
			{
				start_pos.x = j * data->tile_size + data->tile_size / 2;
				start_pos.y = i * data->tile_size + data->tile_size / 2;
				return (start_pos);
			}
			j++;
		}
		i++;
	}
	return ((t_vec2f){0, 0});
}

void	init_player(t_data *data)
{
	data->player.pos = get_start_pos(data);
	data->player.rot_speed = 0.1;
	data->player.angle = 0;
	data->player.speed = data->tile_size / FPS * 2;
	data->player.key_up = false;
	data->player.key_down = false;
	data->player.key_left = false;
	data->player.key_right = false;
	data->player.left_rot = false;
	data->player.right_rot = false;
	mlx_hook(data->win, 2, 1L<<0, key_press, &data->player);
	mlx_hook(data->win, 3, 1L<<1, key_release, &data->player);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1' || data->map[i][j] == ' ')
			{
				draw_square((t_vec2){j * data->tile_size + data->tile_size / 2,
					i * data->tile_size + data->tile_size / 2},
					data->tile_size, 0xFF0000, data);
			}
			j++;
		}
		i++;
	}
}

double distance(double x, double y)
{
    return (sqrt(x * x + y * y));
}

void	draw_wall_column(t_tex *tex, t_wall *wall, t_data *data, int i)
{
	int	y;
	int	tex_y;
	int	color;
	int	offset;

	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		tex_y = (int)tex->tex_pos;
		tex->tex_pos += tex->step;
		offset = tex_y * (tex->tex->line_length / (tex->tex->bpp / 8));
		color = tex->tex->addr[offset + tex->tex_x];
		my_put_pixel((t_vec2){i, y}, color, data);
		y++;
	}
}

void	draw_line(t_data *data, double ray_angle, int i)
{
	t_ray	ray;
	t_dda	dda;
	t_dda2	dda2;
	t_wall	wall;
	t_tex	tex;

	init_ray(&ray, data, ray_angle);
	init_dda(&dda, &ray);
	init_side_dist_x(&dda, data, &ray);
	init_side_dist_y(&dda, &dda2, data, &ray);
	perform_dda(&dda, &ray, &dda2, data);
	calc_wall_dist(&wall, &dda, &dda2);
	calc_line_height(&wall);
	calc_wall_x(&wall, data, &ray, &dda2);
	tex.tex = select_texture(data, &dda, &dda2);
	calc_tex_x(&tex, &wall, &ray, &dda2);
	init_tex_render(&tex, &wall);
	draw_wall_column(&tex, &wall, data, i);
}

void	draw_player(t_data *data)
{
	double	pixel_step = FOV * (PI / 180) / WINDOW_WIDTH;
	double	start_x = data->player.angle - (FOV * (PI / 180) / 2);
	int		i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_line(data, start_x, i);
		start_x += pixel_step;
		i++;
	}
	//draw_square((t_vec2)data->player.pos, data->tile_size / 4, 0x00FF00, data);
}

t_bool	frame_ready(t_data *data)
{
	long	now;
	long	frame_time;

	now = get_time_ms();
	frame_time = 1000 / FPS;
	if (now - data->last_frame >= frame_time)
	{
		data->last_frame = now;
		return (true);
	}
	return (false);
}

void	draw_floor_ceiling(t_data *data)
{
	int	i;
	int	j;
	int	color;
	
	color = 0x57c7d4;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		if (i > WINDOW_HEIGHT / 2)
			color = 0x83bd6f;
		while (j < WINDOW_WIDTH)
		{
			my_put_pixel((t_vec2){j, i}, color, data);
			j++;
		}
		i++;
	}
	
}

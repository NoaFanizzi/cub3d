/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:13:41 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 13:42:19 by nofanizz         ###   ########.fr       */
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

void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_length, &data->endian);
	data->tile_size = get_tile_size(data->map);
	data->last_frame = get_time_ms();
	init_texture(data->mlx, &data->texture[NO], data->texture[NO].path);
	init_texture(data->mlx, &data->texture[SO], data->texture[SO].path);
	init_texture(data->mlx, &data->texture[WE], data->texture[WE].path);
	init_texture(data->mlx, &data->texture[EA], data->texture[EA].path);
	init_player(data);
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

t_bool	touch_wall(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = px / data->tile_size;
	y = py / data->tile_size;
	if (data->map[y][x] == '1' || data->map[y][x] == 'X')
		return (true);
	return (false);
}

double distance(double x, double y)
{
    return (sqrt(x * x + y * y));
}

/* void	draw_line(t_data *data, double start_x, int i)
{
	double	cos_angle = cos(start_x);
	double	sin_angle = sin(start_x);
	double	ray_x = data->player.pos.x;
	double	ray_y = data->player.pos.y;
	
	while (!touch_wall(ray_x, ray_y, data))
	{
		//my_put_pixel((t_vec2){ray_x, ray_y}, 0x0000FF, data);
		ray_x -= cos_angle;
		ray_y += sin_angle;
	}
	double	dist = distance(ray_x - data->player.pos.x, ray_y - data->player.pos.y);
	double	height = (data->tile_size / dist) * (WINDOW_WIDTH / 2);
	int		start_y = (WINDOW_HEIGHT - height) / 2;
	int		end = start_y + height;
	while (start_y < end)
	{
		my_put_pixel((t_vec2){i, start_y}, 0xFF0000, data);
		start_y++;
	}
}
 */

void draw_line(t_data *data, double ray_angle, int i) {
    double cos_angle = cos(ray_angle);
    double sin_angle = sin(ray_angle);

    int map_x = (int)(data->player.pos.x / data->tile_size);
    int map_y = (int)(data->player.pos.y / data->tile_size);

    double dir_x = cos_angle;
    double dir_y = sin_angle;

    double delta_dist_x = (dir_x == 0) ? 1e30 : fabs(1 / dir_x);
    double delta_dist_y = (dir_y == 0) ? 1e30 : fabs(1 / dir_y);

    int step_x = (dir_x < 0) ? -1 : 1;
    int step_y = (dir_y < 0) ? -1 : 1;

    double side_dist_x, side_dist_y;
    if (dir_x < 0)
        side_dist_x = (data->player.pos.x / data->tile_size - map_x) * delta_dist_x;
    else
        side_dist_x = (map_x + 1.0 - data->player.pos.x / data->tile_size) * delta_dist_x;
    if (dir_y < 0)
        side_dist_y = (data->player.pos.y / data->tile_size - map_y) * delta_dist_y;
    else
        side_dist_y = (map_y + 1.0 - data->player.pos.y / data->tile_size) * delta_dist_y;

    int hit = 0;
    int side;
    while (hit == 0) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (map_y >= 0 && map_x >= 0 && data->map[map_y] && data->map[map_y][map_x]) {
            if (data->map[map_y][map_x] == '1' || data->map[map_y][map_x] == 'X')
                hit = 1;
        }
    }

    double perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (side_dist_x - delta_dist_x);
    else
        perp_wall_dist = (side_dist_y - delta_dist_y);

    if (perp_wall_dist < 0.001)
        perp_wall_dist = 0.001;

    int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
    int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_end >= WINDOW_HEIGHT)
        draw_end = WINDOW_HEIGHT - 1;

    double wall_x;
    if (side == 0)
        wall_x = data->player.pos.y / data->tile_size + perp_wall_dist * dir_y;
    else
        wall_x = data->player.pos.x / data->tile_size + perp_wall_dist * dir_x;
    wall_x -= floor(wall_x);

    t_texture *tex;
    if (side == 0) {
        if (step_x > 0)
            tex = &data->texture[EA];
        else
            tex = &data->texture[WE];
    } else {
        if (step_y > 0)
            tex = &data->texture[SO];
        else
            tex = &data->texture[NO];
    }

    int tex_x = (int)(wall_x * (double)tex->width);

    // Correct orientation for texture
    if (side == 0 && dir_x < 0)
        tex_x = tex->width - tex_x - 1;
    if (side == 1 && dir_y > 0)
        tex_x = tex->width - tex_x - 1;
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex->width)
        tex_x = tex->width - 1;

    double step = 1.0 * tex->height / line_height;
    double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

    for (int y = draw_start; y < draw_end; y++) {
        int tex_y = (int)tex_pos;
        tex_pos += step;
        int color = tex->addr[tex_y * (tex->line_length / (tex->bpp / 8)) + tex_x];
        my_put_pixel((t_vec2){i, y}, color, data);
    }
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

int	game_loop(t_data *data)
{
	if (!frame_ready(data))
		return (1);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_length, &data->endian);
	player_movement(&data->player);
	draw_floor_ceiling(data);
	//draw_pov(data);
	//draw_map(data);
	draw_player(data);
	draw_square((t_vec2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, 10, 0xFFFFFF, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/15 17:55:06 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char ***tab)
{
	size_t	i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void	display_tab(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		ft_putendl_fd(map[i], 2);
		i++;
	}
}

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

void	draw_line(t_data *data, double ray_angle, int i)
{
	double	cos_angle = cos(ray_angle);
	double	sin_angle = sin(ray_angle);
	double	ray_x = data->player.pos.x;
	double	ray_y = data->player.pos.y;

	// Step forward until we hit a wall
	while (!touch_wall(ray_x, ray_y, data))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	// Euclidean distance from player to wall
	double dx = ray_x - data->player.pos.x;
	double dy = ray_y - data->player.pos.y;
	double dist = sqrt(dx * dx + dy * dy);

	// Fish-eye correction
	dist *= cos(ray_angle - data->player.angle);

	// Project wall height on screen
	double height = (data->tile_size / dist) * (WINDOW_WIDTH / 2);
	int start_y = (WINDOW_HEIGHT - height) / 2;
	int end_y = start_y + height;

	// Draw vertical wall slice
	while (start_y < end_y && start_y < WINDOW_HEIGHT)
	{
		my_put_pixel((t_vec2){i, start_y}, 0xFF0000, data);
		start_y++;
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

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	(void)argc;
	if (map_parser(argc, argv, &data.map) == 1)
	{
		if (argc == 1)
			ft_putendl_fd("No map sended !", 2);
		else
			ft_putendl_fd("Invalid map sended !", 2);
		return (1);
	}
	init_game(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:16:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/09 20:45:29 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_length, &data->endian);
	data->tile_size = get_tile_size(data->map);
	data->last_frame = get_time_ms();
	//init_menu(data);
	init_texture(data->mlx, &data->texture[NO], data->texture[NO].path);
	init_texture(data->mlx, &data->texture[SO], data->texture[SO].path);
	init_texture(data->mlx, &data->texture[WE], data->texture[WE].path);
	init_texture(data->mlx, &data->texture[EA], data->texture[EA].path);
	init_player(data);
}

int	game_loop(t_data *data)
{
	player_movement(&data->player, data);
	draw_floor_ceiling(data);
	draw_player(data);
	draw_square((t_vec2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, 10, 0xFFFFFF, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int init_menu(t_data *data)
{
	while(1)
		display_menu(data);
	game_loop(data);
}

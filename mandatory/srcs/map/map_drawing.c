/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:39:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/07 16:11:02 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_data *data, int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_tile_color(char c)
{
	if (c == '0')
		return (0xFFFFFF); // Blanc pour le sol
	else if (c == '1')
		return (0x000000); // Noir pour les murs
	else if (ft_strchr("NSEW", c))
		return (0xFF0000); // Rouge pour spawn du joueur
	else
		return (0x808080); // Gris pour les espaces vides
}

void	draw_tile(t_data *data, int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_dot(t_data *data, int tile_size)
{
	int	player_x;
	int	player_y;
	int	dot_size;

	dot_size = 4;
	player_x = (int)(data->player.x * tile_size);
	player_y = (int)(data->player.y * tile_size);
	draw_tile(data, player_x - dot_size / 2, player_y - dot_size / 2, dot_size,
		0x00FF00);
}

void	draw_2d_map(t_data *data)
{
	int	color;

	int x;
	int y;
	int map_width, map_height;
	int offset_x;
	int offset_y;
	
	map_height = 0;
	while (data->map[map_height])
		map_height++;
	map_width = ft_strlen(data->map[0]);
	offset_x = (WINDOW_WIDTH - (map_width * TILE_SIZE)) / 2;
	offset_y = (WINDOW_HEIGHT - (map_height * TILE_SIZE)) / 2;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			color = get_tile_color(data->map[y][x]);
			draw_tile(data, x * TILE_SIZE + offset_x, y * TILE_SIZE + offset_y,
				TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

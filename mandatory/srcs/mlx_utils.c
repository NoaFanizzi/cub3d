/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:29:48 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/09/11 10:12:55 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_tab(&data->map);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	my_put_pixel(t_vec2 pos, int color, t_data *data)
{
	int index;

	if (pos.x >= WINDOW_WIDTH || pos.y >= WINDOW_HEIGHT || pos.x < 0 || pos.y < 0)
		return ;
	index = pos.y * data->line_length + pos.x * data->bits_per_pixel / 8;
	data->addr[index] = color & 0xFF;
	data->addr[index + 1] = (color >> 8) & 0xFF;
	data->addr[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_vec2 pos, int size, int color, t_data *data)
{
	t_vec2	new_pos;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			new_pos.x = pos.x + j - size / 2;
			new_pos.y = pos.y + i - size / 2;
			my_put_pixel(new_pos, color, data);
		}
	}
}

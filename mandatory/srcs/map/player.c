/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:19:37 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/07 15:58:11 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, int dx, int dy)
{
	double	new_y;
	double	new_x;

	new_x = data->player.x + dx * 0.2;
	new_y = data->player.y + dy * 0.2;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
		render_frame(data);
	}
}

int	is_valid_position(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || !data->map[map_y] || map_x < 0 || !data->map[map_y][map_x])
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307) // ESC pour fermer
		close_window(data);
	else if (keycode == 13 || keycode == 119) // W - Haut
		move_player(data, 0, -1);
	else if (keycode == 0 || keycode == 97) // A - Gauche
		move_player(data, -1, 0);
	else if (keycode == 1 || keycode == 115) // S - Bas
		move_player(data, 0, 1);
	else if (keycode == 2 || keycode == 100) // D - Droite
		move_player(data, 1, 0);
	return (0);
}

void	init_player(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.x = (double)x + 0.5;
				data->player.y = (double)y + 0.5;
				data->player.dir_x = 1.0;
				data->player.dir_y = 0.0;
				return ;
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:19:37 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 15:19:24 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(double x, double y, t_data *data)
{
	int map_element_x;
	int map_element_y;

	map_element_x = x / data->tile_size;
	map_element_y = y / data->tile_size;
	printf("map_element_x = %d\n", map_element_x);
	printf("map_element_y = %d\n", map_element_y);
	printf("data->map[map_element_y][map_element_x] = %c\n\n\n", data->map[map_element_y][map_element_x]);
	if(map_element_x < 0 || map_element_y < 0)
		return(1);
	if(!data->map[map_element_y] || !data->map[map_element_y][map_element_x])
		return(1);
	if((data->map[map_element_y][map_element_x] == '1')
		||(data->map[map_element_y][map_element_x] == 'X'))
			return(1);
	return(0);
}

int	check_collisions_with_margins(double x, double y, double margin, t_data *data)
{
	if(is_wall(x + margin, y,  data) == 1)
		return(1);
	if(is_wall(x - margin, y, data) == 1)
		return(1);
	if(is_wall(x, y + margin, data) == 1)
		return(1);
	if(is_wall(x, y - margin, data) == 1)
		return(1);
	return(0);
}

void	check_collisions(t_player *player, t_data *data, t_vec2f *old_pos, t_vec2f *new_pos)
{
	double margin;

	margin = data->tile_size * 0.2;

	if(check_collisions_with_margins(new_pos->x, new_pos->y, margin, data) == 1)
	{
		if(check_collisions_with_margins(old_pos->x, new_pos->y, margin, data) == 0)
		{
			player->pos.x = old_pos->x;
			return;
		}
		if(check_collisions_with_margins(new_pos->x, old_pos->y, margin, data) == 1)
		{
			player->pos.y = old_pos->y;
			return;		
		}
		player->pos.x = old_pos->x;
		player->pos.y = old_pos->y;
	}
}

void	player_movement(t_player *player, t_data *data)
{
	double	cos_angle;
	double	sin_angle;
	t_vec2f old_pos;

	
	if (player->left_rot)
		player->angle -= player->rot_speed;
	if (player->right_rot)
		player->angle += player->rot_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
		
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	old_pos.x = player->pos.x;
	old_pos.y = player->pos.y;
	if (player->key_up)
	{
		player->pos.x += cos_angle * player->speed;
		player->pos.y += sin_angle * player->speed;
	}
	if (player->key_down)
	{
		player->pos.x -= cos_angle * player->speed;
		player->pos.y -= sin_angle * player->speed;
	}
	if (player->key_left)
	{
		player->pos.x += sin_angle * player->speed;
		player->pos.y -= cos_angle * player->speed;
	}
	if (player->key_right)
	{
		player->pos.x -= sin_angle * player->speed;
		player->pos.y += cos_angle * player->speed;
	}
	check_collisions(player, data, &old_pos, &player->pos);
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == RIGHT)
		player->right_rot = true;
	if (keycode == LEFT)
		player->left_rot = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == RIGHT)
		player->right_rot = false;
	if (keycode == LEFT)
		player->left_rot = false;
	return (0);
}

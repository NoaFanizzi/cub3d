/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:19:37 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 16:13:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

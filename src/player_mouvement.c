/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:52:58 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/11/30 16:14:39 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_bool	check_collision(char move, t_player *p, char **map)
{
	int new_x;
	int	new_y;

	if (move == 'U')
	{
		new_x = (int)(p->x + p->dir_x * p->move_speed * 1.2);
		new_y = (int)(p->y + p->dir_y * p->move_speed * 1.2);
	}
	else if (move == 'D')
	{
		new_x = (int)(p->x - p->dir_x * p->move_speed * 1.2);
		new_y = (int)(p->y - p->dir_y * p->move_speed * 1.2);
	}
	else if (move == 'R')
	{
		new_x = (int)(p->x + p->plane_x * p->move_speed * 1.2);
		new_y = (int)(p->y + p->plane_y * p->move_speed * 1.2);
	}
	else
	{
		new_x = (int)(p->x - p->plane_x * p->move_speed * 1.2);
		new_y = (int)(p->y - p->plane_y * p->move_speed * 1.2);
	}
	return (map[new_y][new_x] != '1');
}

static void rotate_player(t_player *p, double angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void player_movement(t_player *p, char **map)
{
	if (p->up && check_collision('U', p, map))
	{
		p->x += p->dir_x * p->move_speed;
		p->y += p->dir_y * p->move_speed;
	}
	if (p->down && check_collision('D', p, map))
	{
		p->x -= p->dir_x * p->move_speed;
		p->y -= p->dir_y * p->move_speed;
	}
	if (p->right && check_collision('R', p, map))
	{
		p->x += p->plane_x * p->move_speed;
		p->y += p->plane_y * p->move_speed;
	}
	if (p->left && check_collision('L', p, map))
	{
		p->x -= p->plane_x * p->move_speed;
		p->y -= p->plane_y * p->move_speed;
	}
	if (p->arrow_r)
		rotate_player(p, p->rot_speed);
	if (p->arrow_l)
		rotate_player(p, -p->rot_speed);
}

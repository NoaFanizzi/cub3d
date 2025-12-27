/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:35:23 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:35:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray_step_side(t_game *g)
{
	if (g->ray.dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_x = (g->player.x - g->ray.map_x) * g->ray.delta_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_x = (g->ray.map_x + 1.0 - g->player.x) * g->ray.delta_x;
	}
	if (g->ray.dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_y = (g->player.y - g->ray.map_y) * g->ray.delta_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_y = (g->ray.map_y + 1.0 - g->player.y) * g->ray.delta_y;
	}
}

void	init_ray(t_game *g, int x)
{
	g->ray.hit = 0;
	g->ray.side = 0;
	g->ray.camera_x = 2 * x / (double)WIDTH - 1;
	g->ray.dir_x = g->player.dir_x + g->player.plane_x * g->ray.camera_x;
	g->ray.dir_y = g->player.dir_y + g->player.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)g->player.x;
	g->ray.map_y = (int)g->player.y;
	if (g->ray.dir_x == 0)
		g->ray.delta_x = 1e30;
	else
		g->ray.delta_x = fabs(1 / g->ray.dir_x);
	if (g->ray.dir_y == 0)
		g->ray.delta_y = 1e30;
	else
		g->ray.delta_y = fabs(1 / g->ray.dir_y);
	init_ray_step_side(g);
}

void	check_hit(t_game *g)
{
	while (!g->ray.hit)
	{
		if (g->ray.side_x < g->ray.side_y)
		{
			g->ray.side_x += g->ray.delta_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_y += g->ray.delta_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}
		if (g->cfg.map[g->ray.map_y][g->ray.map_x] == '1')
			g->ray.hit = 1;
	}
}

void	raycasting(t_game *g)
{
	t_tex	*tex;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(g, x);
		check_hit(g);
		if (g->ray.side == 0)
			g->ray.perp_dist = (g->ray.side_x - g->ray.delta_x);
		else
			g->ray.perp_dist = (g->ray.side_y - g->ray.delta_y);
		g->ray.line_height = (int)(HEIGHT / g->ray.perp_dist);
		g->ray.draw_start = -g->ray.line_height / 2 + HEIGHT / 2;
		g->ray.draw_end = g->ray.line_height / 2 + HEIGHT / 2;
		tex = choose_tex(g);
		find_texture_x(&g->ray, &g->player, tex);
		draw_vertical_text(&g->mlx_cfg, x, &g->ray, tex);
		x++;
	}
}

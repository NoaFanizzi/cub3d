/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:13:14 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 17:01:23 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	calc_tex_x(t_tex *tex, t_wall *wall, t_ray *ray, t_dda2 *dda2)
{
	tex->tex_x = (int)(wall->wall_x * (double)tex->tex->width);
	if (dda2->side == 0 && ray->cos_angle < 0)
		tex->tex_x = tex->tex->width - tex->tex_x - 1;
	if (dda2->side == 1 && ray->sin_angle > 0)
		tex->tex_x = tex->tex->width - tex->tex_x - 1;
	if (tex->tex_x < 0)
		tex->tex_x = 0;
	if (tex->tex_x >= tex->tex->width)
		tex->tex_x = tex->tex->width - 1;
}

void	calc_wall_x(t_wall *wall, t_data *data, t_ray *ray, t_dda *dda, t_dda2 *dda2)
{
	if (dda2->side == 0)
		wall->wall_x = data->player.pos.y / data->tile_size;
	else
		wall->wall_x = data->player.pos.x / data->tile_size;
	
	if (dda2->side == 0)
		wall->wall_x += (ray->map_x - data->player.pos.x / data->tile_size 
			+ (1 - dda->step_x) / 2.0) / ray->cos_angle * ray->sin_angle;
	else
		wall->wall_x += (ray->map_y - data->player.pos.y / data->tile_size 
			+ (1 - dda2->step_y) / 2.0) / ray->sin_angle * ray->cos_angle;
	
	wall->wall_x -= floor(wall->wall_x);
}

void	calc_wall_dist(t_wall *wall, t_dda *dda, t_dda2 *dda2)
{
	if (dda2->side == 0)
		wall->perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		wall->perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	if (wall->perp_wall_dist < 0.001)
		wall->perp_wall_dist = 0.001;
}

void	calc_line_height(t_wall *wall)
{
	wall->line_height = (int)(WINDOW_HEIGHT / wall->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + WINDOW_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + WINDOW_HEIGHT / 2;
	if (wall->draw_end >= WINDOW_HEIGHT)
		wall->draw_end = WINDOW_HEIGHT - 1;
}

void	init_ray(t_ray *ray, t_data *data, double ray_angle)
{
	ray->cos_angle = cos(ray_angle);
	ray->sin_angle = sin(ray_angle);
	ray->map_x = (int)(data->player.pos.x / data->tile_size);
	ray->map_y = (int)(data->player.pos.y / data->tile_size);
}

void	init_side_dist_x(t_dda *dda, t_data *data, t_ray *ray)
{
	double	player_grid_x;

	player_grid_x = data->player.pos.x / data->tile_size;
	if (ray->cos_angle < 0)
		dda->side_dist_x = (player_grid_x - ray->map_x) * dda->delta_dist_x;
	else
		dda->side_dist_x = (ray->map_x + 1.0 - player_grid_x) * dda->delta_dist_x;
}

void	init_side_dist_y(t_dda *dda, t_dda2 *dda2, t_data *data, t_ray *ray)
{
	double	player_grid_y;

	player_grid_y = data->player.pos.y / data->tile_size;
	if (ray->sin_angle < 0)
	{
		dda->side_dist_y = (player_grid_y - ray->map_y) * dda->delta_dist_y;
		dda2->step_y = -1;
	}
	else
	{
		dda->side_dist_y = (ray->map_y + 1.0 - player_grid_y) * dda->delta_dist_y;
		dda2->step_y = 1;
	}
}
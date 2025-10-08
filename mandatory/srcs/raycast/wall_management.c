/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:15:11 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 18:49:47 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	is_wall(double x, double y, t_data *data)
{
	int map_element_x;
	int map_element_y;

	map_element_x = x / data->tile_size;
	map_element_y = y / data->tile_size;
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
	if(is_wall(x + margin, y + margin,  data) == 1)
		return(1);
	if(is_wall(x - margin, y + margin, data) == 1)
		return(1);
	if(is_wall(x + margin, y - margin, data) == 1)
		return(1);
	if(is_wall(x - margin, y - margin, data) == 1)
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
		if(check_collisions_with_margins(new_pos->x, old_pos->y, margin, data) == 0)
		{
			player->pos.y = old_pos->y;
			return;		
		}
		player->pos.x = old_pos->x;
		player->pos.y = old_pos->y;
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

int	check_wall_hit(t_data *data, t_ray *ray)
{
	char	cell;

	if (ray->map_y < 0 || ray->map_x < 0)
		return (0);
	if (!data->map[ray->map_y] || !data->map[ray->map_y][ray->map_x])
		return (0);
	cell = data->map[ray->map_y][ray->map_x];
	if (cell == '1' || cell == 'X')
		return (1);
	return (0);
}
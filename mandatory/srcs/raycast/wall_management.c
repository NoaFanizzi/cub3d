/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:15:11 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 16:15:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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
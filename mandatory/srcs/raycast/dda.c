/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:14:05 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/26 14:15:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	perform_dda(t_dda *dda, t_ray *ray, t_data *data)
{
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			ray->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			ray->map_y += dda->step_y;
			dda->side = 1;
		}
		if (check_wall_hit(data, ray))
			break;
	}
}

void	init_dda(t_dda *dda, t_ray *ray)
{
	if (ray->cos_angle == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / ray->cos_angle);//dda->delta_dist_x = fabs(1 / ray->cos_angle);
	if (ray->sin_angle == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / ray->sin_angle);
	if (ray->cos_angle < 0)
		dda->step_x = -1;
	else
		dda->step_x = 1;
}

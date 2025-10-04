/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:14:05 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/04 16:14:56 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	dda_step_x(t_dda *dda, t_ray *ray, t_dda2 *dda2)
{
	dda->side_dist_x += dda->delta_dist_x;
	ray->map_x += dda->step_x;
	dda2->side = 0;
}

void	dda_step_y(t_dda *dda, t_ray *ray, t_dda2 *dda2)
{
	dda->side_dist_y += dda->delta_dist_y;
	ray->map_y += dda2->step_y;
	dda2->side = 1;
}

void	perform_dda(t_dda *dda, t_ray *ray, t_dda2 *dda2, t_data *data)
{
	dda2->hit = 0;
	while (dda2->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
			dda_step_x(dda, ray, dda2);
		else
			dda_step_y(dda, ray, dda2);
		if (check_wall_hit(data, ray))
			dda2->hit = 1;
	}
}

void	init_dda(t_dda *dda, t_ray *ray)
{
	if (ray->cos_angle == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / ray->cos_angle);
	if (ray->sin_angle == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / ray->sin_angle);
	if (ray->cos_angle < 0)
		dda->step_x = -1;
	else
		dda->step_x = 1;
}
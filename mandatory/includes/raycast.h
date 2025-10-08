#ifndef RAYCAST_H
#define RAYCAST_H

#include "cub3d.h"

//dda.c
void	dda_step_x(t_dda *dda, t_ray *ray, t_dda2 *dda2);
void	dda_step_y(t_dda *dda, t_ray *ray, t_dda2 *dda2);
void	perform_dda(t_dda *dda, t_ray *ray, t_dda2 *dda2, t_data *data);
void	init_dda(t_dda *dda, t_ray *ray);

//raycast.c
void	calc_tex_x(t_tex *tex, t_wall *wall, t_ray *ray, t_dda2 *dda2);
void	calc_wall_x(t_wall *wall, t_data *data, t_ray *ray, t_dda *dda, t_dda2 *dda2);
void	calc_wall_dist(t_wall *wall, t_dda *dda, t_dda2 *dda2);
void	calc_line_height(t_wall *wall);
void	init_ray(t_ray *ray, t_data *data, double ray_angle);
void	init_side_dist_x(t_dda *dda, t_data *data, t_ray *ray);
void	init_side_dist_y(t_dda *dda, t_dda2 *dda2, t_data *data, t_ray *ray);

//wall_management.c
int	    is_wall(double x, double y, t_data *data);
int	    check_collisions_with_margins(double x, double y, double margin, t_data *data);
void	check_collisions(t_player *player, t_data *data, t_vec2f *old_pos, t_vec2f *new_pos);
t_bool	touch_wall(double px, double py, t_data *data);
int     check_wall_hit(t_data *data, t_ray *ray);

#endif
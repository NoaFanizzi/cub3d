#ifndef DRAWING_H
#define DRAWING_H

#include "cub3d.h"

int	        get_tile_size(char **map);
t_vec2f	    get_start_pos(t_data *data);
void	    init_player(t_data *data);
long	    get_time_ms(void);
void	    draw_map(t_data *data);
double      distance(double x, double y);
void	    draw_wall_column(t_tex *tex, t_wall *wall, t_data *data, int i);
void		draw_line(t_data *data, double ray_angle, int i);
void        draw_player(t_data *data);
t_bool      frame_ready(t_data *data);
void	    draw_floor_ceiling(t_data *data);


#endif
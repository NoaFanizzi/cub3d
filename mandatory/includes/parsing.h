# ifndef PARSING_H
# define PARSING_H

#include "struct.h"

//map_parsing.c
int		is_suffix_correct(char *str);
int		check_width(char **map);
int		check_border(char **map);
int		map_parser(int argc, char **argv, char ***map);

//map_init.c
void	resize_map(char ***map, char ***new_map, char **temp, int is_last);
void	load_delimitation_line(char **trimmed_map, size_t length);
void	add_last_line(char ***map);
int		update_map(char ***map, char **temp);
char	**get_map(char **argv);

//map_utils.c
void	get_map_size(t_size *size, char ***map);
void	get_tab_length(char ***tab, size_t *length);
int		get_last_line_pos(char ***map);
int		get_last_line_length(char ***map);
void	replace_char(char ***map, char old, char new);

//map_drawing.c
int		get_tile_color(char c);
void	draw_tile(t_data *data, int start_x, int start_y, int size, int color);
void	draw_player_dot(t_data *data, int tile_size);
void	draw_2d_map(t_data *data);

//player.c
void	move_player(t_data *data, int dx, int dy);
int		is_valid_position(t_data *data, double x, double y);
int		key_hook(int keycode, t_data *data);
void	init_player(t_data *data);

//window_creation.c
int		render_frame(t_data *data);
int		windows_creation(t_data *data);
int		close_window(t_data *data);
int		get_map_width(t_data *data);
int		get_map_height(t_data *data);
int		init_mlx(t_data *data);


# endif
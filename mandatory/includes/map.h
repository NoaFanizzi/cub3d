#ifndef MAP_H
#define MAP_H

#include "cub3d.h"

//map_init.c
int	        update_map(char ***map, char **temp);
int	        is_map_suffix_correct(t_data *data, char *suffix);
char	    **get_map(char **argv, t_data *data);

//map_parsing.c
int	        is_suffix_correct(char *str, char *suffix);
int	        check_width(char **map);
int	        check_border(char **map);
int	        check_validity(char **map);
int         map_parser(int argc, char **argv, char ***map, t_data *data);

//map_resizing.c
void	    add_last_line(char ***map);
void	    load_delimitation_line(char **trimmed_map, size_t length);
void	    resize_map(char ***map, char ***new_map, char **temp, int is_last);

//map_textures_management.c
void        init_texture(void *mlx_ptr, t_texture *texture, char *file_path);
t_texture	*select_texture(t_data *data, t_dda *dda, t_dda2 *dda2);
void	    init_tex_render(t_tex *tex, t_wall *wall);
int         parse_textures(int fd, t_data *data);

//map_utils.c
void	    display_texture_data(t_data *data);
void	    get_map_size(t_size *size, char ***map);
void	    get_tab_length(char ***tab, size_t *length);
int         get_last_line_pos(char ***map);
int         get_last_line_length(char ***map);
void	    replace_char(char ***map, char old, char new, t_data *data);

#endif
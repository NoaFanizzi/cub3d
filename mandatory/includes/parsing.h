# ifndef PARSING_H
# define PARSING_H

#include "struct.h"

//map_parsing.c
int		is_suffix_correct(char *str);
int		check_width(char **map);
int		check_border(char **map);
int		map_parser(int argc, char **argv);

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



# endif
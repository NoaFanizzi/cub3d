#ifndef CUB3D_H
#define CUB3D_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_size
{
	size_t	x;
	size_t	y;
}				t_size;

void	get_map_size(t_size *size, char ***map);
void	get_tab_length(char ***tab, size_t *length);
void	resize_map(char ***map, char ***new_map, char **temp);
int		update_map(char ***map, char **temp);
char	**get_map(char **argv);

int		is_suffix_correct(char *str);
int		check_width(char **map);
int		check_border(char **map);
int		map_parser(int argc, char **argv);

void	free_tab(char ***tab);
void	display_tab(char **map);


#endif
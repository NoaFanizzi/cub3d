/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:19:01 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:28:10 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "libft.h"
#include "stdlib.h" 
#include "cube.h"

//map_colors.c
int		parse_color_line(char *line, char identifier, int *color_array);

//map_init.c
char	**get_map(char **argv, t_config *config);

//map_line_management.c
int		check_and_add_texture(char *temp, const char *prefix, char **dest);
int		init_first_lines(char ***new_map, char *line);
void	load_delimitation_line(char **trimmed_map, size_t length);
void	add_last_line(char ***map);

//map_resizing.c
int		update_map(char ***map, char **temp);
int     resize_map(char ***map, char ***new_map, char **temp, int is_last);

//map_utils.c
int		handle_map_error(char **line, char ***map, int fd);
int		handle_map_case(char **line, int *map_started, char ***map, int fd);
int		is_str_digit(char *str);
int		validate_line_format(char *line, char identifier);

#endif
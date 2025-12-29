/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:20:09 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:30:21 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cube.h"

// parsing_syntax.c
int		is_suffix_correct(char *str, char *suffix);
int		is_map_suffix_correct(t_config *config, char *suffix);
int		is_only_space(char *str);

// parsing_map.c
int		check_validity(char **map);
int		check_border(char **map);
int		map_parser(int argc, char **argv, char ***map, t_config *config);

// parsing_texture.c
int		parse_textures(int fd, t_config *config);

// parsing_config.c
int		parse_config_line(char *line, t_config *config);
int		is_config_complete(t_config *config);

// parsing_utils.c
void	replace_char(char ***map, char old, char nw, t_config *config);
void	get_tab_length(char ***tab, size_t *length);
int		get_last_line_pos(char ***map);
int		get_last_line_length(char ***map);
void	get_tab_length(char ***tab, size_t *length);

#endif
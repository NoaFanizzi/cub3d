/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:24:29 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:32:45 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cube.h"

// control_key.c
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

// game_loop.c
int			rgb_to_color(int rgb[3]);
long long	get_time_micro(void);
void		limit_fps(t_game *game);
void		color_ceiling_floor(t_game *game);
int			game_loop(t_game *game);

// init_player.c
int			init_player(t_game *game);

// player_movement.c
void		player_movement(t_player *p, char **map);

#endif

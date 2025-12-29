/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:25:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:34:21 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cube.h"

// raycasting_texture.c
t_tex	*choose_tex(t_game *g);
void	find_texture_x(t_ray *ray, t_player *p, t_tex *tex);
void	find_texture_step(t_ray *ray, t_tex *tex);
void	draw_vertical_text(t_mlx *mlx, int x, t_ray *ray, t_tex *tex);

// raycasting.c
t_bool	is_power_two(int n);
void	init_ray_step_side(t_game *g);
void	init_ray(t_game *g, int x);
void	check_hit(t_game *g);
void	raycasting(t_game *g);

#endif
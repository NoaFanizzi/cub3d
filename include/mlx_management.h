/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:23:02 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:40:38 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MANAGEMENT_H
#define MLX_MANAGEMENT_H

#include "cube.h"

//mlx_init.c
t_bool	init_mlx(t_game *game);

//mlx_cleaning.c
void	cleanup_mlx(t_mlx *config);
void	cleanup_window(t_mlx *config);
void	cleanup_image(t_mlx *config);
int		mlx_clean(t_mlx *config);


//mlx_config.c
void	my_put_pixel(t_mlx *mlx, int x, int y, int color);
int		close_window(t_game *game);
t_bool	init_textures(t_game *game);

#endif
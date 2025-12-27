/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:15:06 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:17:24 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_bool	init_mlx_instance(t_mlx *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
	{
		write(2, "mlx_init() fail\n", 17);
		return (false);
	}
	return (true);
}

static t_bool	init_window(t_mlx *config)
{
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!config->win)
	{
		write(2, "mlx_new_window() fail\n", 23);
		cleanup_mlx(config);
		return (false);
	}
	return (true);
}

static t_bool	init_image(t_mlx *config)
{
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img)
	{
		cleanup_window(config);
		return (false);
	}
	config->addr = mlx_get_data_addr(config->img, &config->bpp,
			&config->size_line, &config->endian);
	return (true);
}

static t_bool	init_all_textures(t_game *game)
{
	if (!init_textures(game))
	{
		cleanup_image(&game->mlx_cfg);
		return (false);
	}
	return (true);
}

t_bool	init_mlx(t_game *game)
{
	t_mlx	*config;

	config = &game->mlx_cfg;
	if (!init_mlx_instance(config))
		return (false);
	if (!init_window(config))
		return (false);
	if (!init_image(config))
		return (false);
	if (!init_all_textures(game))
		return (false);
	game->last_frame = get_time_micro();
	return (true);
}
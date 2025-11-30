/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:19:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/30 13:00:42 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//free all mlx pointers
int	mlx_clean(t_mlx *config)
{
	if (config->img)
		mlx_destroy_image(config->mlx, config->img);
	if (config->win)
		mlx_destroy_window(config->mlx, config->win);
	mlx_destroy_display(config->mlx);
	free(config->mlx);
	return (0);
}

//to call after escape or cross click
int	close_window(t_game *game)
{
	mlx_clean(&game->mlx_cfg);
	exit(0);
}

//init mlx
t_bool	init_mlx(t_mlx *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
	{
		write(2, "mlx_init() fail\n", 17);
		return (false);
	}
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!config->win)
	{
		write(2, "mlx_new_window() fail\n", 17);
		return (false);
	}
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->addr = (int *)mlx_get_data_addr(config->img, &config->bpp,
		&config->size_line, &config->endian);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:19:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/18 18:39:42 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void my_put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));

    *(unsigned int *)dst = color;
}

//to call after escape or cross click
int	close_window(t_game *game)
{
	mlx_clean(&game->mlx_cfg);
	exit(0);
}

static t_bool	init_xpm_texture(t_tex *tex, void *mlx, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		perror("failed to load img ");
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (false);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
		&tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		perror("mlx_get_data_addr() fail\n");
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		return (false);
	}
	tex->path = path;
	return (true);
}

static t_bool	init_textures(t_game *game)
{
	if (!init_xpm_texture(&game->tex[0], game->mlx_cfg.mlx, game->cfg.tex_no))
		return (false);
	if (!init_xpm_texture(&game->tex[1], game->mlx_cfg.mlx, game->cfg.tex_so))
	{
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[0].img);
		return (false);
	}
	if (!init_xpm_texture(&game->tex[2], game->mlx_cfg.mlx, game->cfg.tex_we))
	{
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[0].img);
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[1].img);
		return (false);
	}
	if (!init_xpm_texture(&game->tex[3], game->mlx_cfg.mlx, game->cfg.tex_ea))
	{
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[0].img);
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[1].img);
		mlx_destroy_image(game->mlx_cfg.mlx, game->tex[2].img);
		return (false);
	}
	return (true);
}

//init mlx
t_bool	init_mlx(t_game *game)
{
	t_mlx	*config;

	config = &game->mlx_cfg;
	config->mlx = mlx_init();
	if (!config->mlx)
	{
		write(2, "mlx_init() fail\n", 17);
		return (false);
	}
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!config->win)
	{
		write(2, "mlx_new_window() fail\n", 23);
		mlx_destroy_display(config->mlx);
		free(config->mlx);
		return (false);
	}
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img)
	{
		mlx_destroy_window(config->mlx, config->win);
		mlx_destroy_display(config->mlx);
		free(config->mlx);
		return (false);
	}
	config->addr = mlx_get_data_addr(config->img, &config->bpp,
		&config->size_line, &config->endian);
	if (!init_textures(game))
	{
		mlx_destroy_image(config->mlx, config->img);
		mlx_destroy_window(config->mlx, config->win);
		mlx_destroy_display(config->mlx);
		free(config->mlx);
		return (false);
	}
	game->last_frame = get_time_micro();
	return (true);
}

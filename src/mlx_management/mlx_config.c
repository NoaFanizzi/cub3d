/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:19:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/29 10:57:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_management.h"

void	my_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

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
		ft_putstr_fd("Error\n", 2);
		return (false);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
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

t_bool	init_textures(t_game *game)
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

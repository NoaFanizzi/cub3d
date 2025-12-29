/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:47:17 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/29 11:10:49 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "map.h"
#include "mlx_management.h"
#include "player.h"
#include "parsing.h"

void	set_null_game(t_game *game)
{
	game->cfg.tex_no = NULL;
	game->cfg.tex_so = NULL;
	game->cfg.tex_we = NULL;
	game->cfg.tex_ea = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	set_null_game(&game);
	if (map_parser(argc, argv, &game.cfg.map, &game.cfg) == 1)
	{
		clean_texture(&game.cfg);
		if (argc == 1)
			ft_putstr_fd("Error\n", 2);
		else
			ft_putstr_fd("Error\n", 2);
		return (1);
	}
	if (!init_player(&game) || !init_mlx(&game))
	{
		clean_texture(&game.cfg);
		free_tab(&game.cfg.map);
		return (1);
	}
	mlx_loop_hook(game.mlx_cfg.mlx, game_loop, &game);
	mlx_hook(game.mlx_cfg.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx_cfg.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx_cfg.win, CROSS, 0, clean_game, &game);
	mlx_loop(game.mlx_cfg.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:47:17 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/30 14:23:41 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (map_parser(argc, argv, &game.cfg.map, &game.cfg) == 1)
	{
		if (argc == 1)
			ft_putstr_fd("No map sent !\n", 2);
		else
			ft_putstr_fd("Invalid map sent !\n", 2);
		return (1);
	}
	if (!init_player(&game) || !init_mlx(&game))
		return (1);
	mlx_loop_hook(game.mlx_cfg.mlx, game_loop, &game);
	mlx_hook(game.mlx_cfg.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.mlx_cfg.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.mlx_cfg.win, CROSS, 0, clean_game, &game);
	mlx_loop(game.mlx_cfg.mlx);
	return 0;
}

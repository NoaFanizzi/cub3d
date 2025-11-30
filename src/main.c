/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:47:17 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/30 11:04:26 by nofanizz         ###   ########.fr       */
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
	if (!init_player(&game) || !init_mlx(&game.mlx_cfg))
	{
		//free
		return (1);
	}
	mlx_loop_hook(game.mlx_cfg.mlx, game_loop, &game);
	mlx_loop(game.mlx_cfg.mlx);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 18:49:21 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_tab(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		ft_putendl_fd(map[i], 2);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	(void)argc;
	if (map_parser(argc, argv, &data.map, &data) == 1)
	{
		if (argc == 1)
			ft_putendl_fd("No map sended !", 2);
		else
			ft_putendl_fd("Invalid map sended !", 2);
		return (1);
	}
	display_tab(data.map);
	init_game(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}

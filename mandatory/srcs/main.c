/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/09 10:37:31 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char ***tab)
{
	size_t	i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

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
	char	**map;

	map = NULL;
	if (map_parser(argc, argv, &data.map) == 1)
	{
		if (argc == 1)
			ft_putendl_fd("No map sended !", 2);
		else
			ft_putendl_fd("Invalid map sended !", 2);
		return (1);
	}
	data.map = map;
	init_player(&data);
	if (init_mlx(&data) == 1)
		return (1);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	render_frame(&data);
	mlx_loop(data.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/07 13:43:14 by nofanizz         ###   ########.fr       */
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
	if (map_parser(argc, argv) == 1)
	{
		if (argc == 1)
			ft_putendl_fd("No map sended !", 2);
		else
			ft_putendl_fd("Invalid map sended !", 2);
		return (1);
	}
	windows_creation();
}

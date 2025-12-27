/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:04:23 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:26:17 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	remove_last_char(char *str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		str[i - 1] = '\0';
}

void	free_tab(char ***tab)
{
	size_t	i;

	if (!tab || !(*tab))
		return ;
	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_wipe(char **str)
{
	free(*str);
	*str = NULL;
}

void	clean_texture(t_config *config)
{
	if (config->tex_no)
		free(config->tex_no);
	if (config->tex_so)
		free(config->tex_so);
	if (config->tex_ea)
		free(config->tex_ea);
	if (config->tex_we)
		free(config->tex_we);
	config->tex_no = NULL;
	config->tex_so = NULL;
	config->tex_ea = NULL;
	config->tex_we = NULL;
}

int	clean_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx_cfg.mlx, game->tex[i].img);
		i++;
	}
	mlx_clean(&game->mlx_cfg);
	clean_texture(&game->cfg);
	free_tab(&game->cfg.map);
	exit(0);
	return (0);
}

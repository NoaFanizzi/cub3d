/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:04:23 by nofanizz          #+#    #+#             */
/*   Updated: 2025/11/30 13:12:01 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void remove_last_char(char *str)
{
    size_t i;

    if (!str)
        return;
    i = 0;
    while (str[i])
        i++;
    if (i > 0)
        str[i - 1] = '\0';
}

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

void    ft_wipe(char **str)
{
    free(*str);
    *str = NULL;
}

void    clean_texture(t_config *config)
{
    free(config->tex_no);
	free(config->tex_so);
	free(config->tex_ea);
	free(config->tex_we);
}

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

int	clean_game(t_game *game)
{
	mlx_clean(&game->mlx_cfg);
	clean_texture(&game->cfg);
	free_tab(&game->cfg.map);
	exit(0);
	return (0);
}

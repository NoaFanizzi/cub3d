/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cleaning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:17:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 10:26:22 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cleanup_mlx(t_mlx *config)
{
	mlx_destroy_display(config->mlx);
	free(config->mlx);
}

void	cleanup_window(t_mlx *config)
{
	mlx_destroy_window(config->mlx, config->win);
	cleanup_mlx(config);
}

void	cleanup_image(t_mlx *config)
{
	mlx_destroy_image(config->mlx, config->img);
	cleanup_window(config);
}

// free all mlx pointers
int	mlx_clean(t_mlx *config)
{
	if (config->img)
		mlx_destroy_image(config->mlx, config->img);
	if (config->win)
		mlx_destroy_window(config->mlx, config->win);
	if (config->mlx)
	{
		mlx_destroy_display(config->mlx);
		free(config->mlx);
	}
	return (0);
}

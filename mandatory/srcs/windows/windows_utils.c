/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:37:21 by nofanizz          #+#    #+#             */
/*   Updated: 2025/09/07 16:03:44 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_data(t_data *data)
{
	if (data->map)
		free_tab(&data->map);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
}

int	close_window(t_data *data)
{
	if (data->map)
		free_tab(&data->map);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	get_map_width(t_data *data)
{
	if (!data->map[0])
		return (0);
	return (ft_strlen(data->map[0]));
}

int	get_map_height(t_data *data)
{
	int	height;

	height = 0;
	while (data->map[height])
		height++;
	return (height);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (data->win == NULL)
		return (1);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

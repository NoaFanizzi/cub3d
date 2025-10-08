/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/08 23:24:11 by nofanizz         ###   ########.fr       */
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

int	is_a_pannel(t_track track[4], t_vec2 pos)
{
	size_t	i;

	i = 0;
	while(i < 2)
	{
		if((track[i].left.y <= pos.y && track[i].right.y >= pos.y)
			&&(track[i].left.x <= pos.x && track[i].right.x >= pos.x))
			return(1);
		i++;
	}
	return(0);
}

int	get_pannel_color(t_track *track, t_vec2 pos)
{
	if(is_a_pannel(track, pos) == 1)
	{
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		return(0xE8E9EB);
	}
	return(0x1A2F4D);
}

void	load_pannel_dimensions(t_track track[4])
{
	int center;
	size_t	i;
	double	saved_scale;

	i = 0;
	saved_scale = 0.85;
	while(i < 4)
	{
		center = WINDOW_WIDTH / 2;
		track[0].left.x = center - (WINDOW_WIDTH / 12);
		track[0].right.x = center + (WINDOW_WIDTH / 12);
		center = WINDOW_HEIGHT * saved_scale;
		saved_scale -= 0.10;
		printf("saved_scale= %f\n", saved_scale);
		track[0].left.y = center * 0.96875;
		track[0].right.y = center * 1.03125; // la plage est de 0.03125
		i++;
	}
	center = WINDOW_WIDTH / 2;
	printf("center.y = %d\n", center);
	track[0].left.x = center - (WINDOW_WIDTH / 12);
	track[0].right.x = center + (WINDOW_WIDTH / 12);
	//center = (WINDOW_HEIGHT / 4) / 2;
	center = WINDOW_HEIGHT * 0.85;
	printf("center.x = %d\n", center);
	track[0].left.y = center * 0.96875;
	track[0].right.y = center * 1.03125; // la plage est de 0.03125

	printf("track.left.y = %d\n", track[0].left.y);
	printf("track.right.y = %d\n", track[0].right.y);
	printf("track.left.x = %d\n", track[0].left.x);
	printf("track.right.x = %d\n", track[0].right.x);

	center = WINDOW_WIDTH / 2;
	track[1].left.x = center - (WINDOW_WIDTH / 12);
	track[1].right.x = center + (WINDOW_WIDTH / 12); //- (WINDOW_HEIGHT * 0.85)
	center = WINDOW_HEIGHT * 0.75;
	track[1].left.y = center * 0.96875;
	track[1].right.y = center * 1.03125;
}

void	display_menu(t_data *data)
{
	t_vec2 pos;
	int 	color;
	int		center;
	t_track		track[4];
	//int		pixels;

	pos.y = 0;
	color = 0x1A2F4D;
	center = 0;

	load_pannel_dimensions(track);
	//exit(0);
	while(pos.y < WINDOW_HEIGHT)
	{
		pos.x = 0;
		while(pos.x < WINDOW_WIDTH)
		{
			color = get_pannel_color(track, pos);
			my_put_pixel(pos, color, data);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	while(1)
		center++;
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	(void)argc;

	if (map_parser(argc, argv, &data.map, &data) == 1)
	{
		if (argc == 1)
			ft_putendl_fd("No map sent !", 2);
		else
			ft_putendl_fd("Invalid map sent !", 2);
		return (1);
	}
	display_tab(data.map);
	init_game(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}

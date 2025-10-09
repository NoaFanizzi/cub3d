/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:31:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/10/09 18:34:58 by nofanizz         ###   ########.fr       */
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

void	load_pannel_dimensions(t_track track[5])
{
	int center;
	size_t	i;
	double	saved_scale;

	i = 1;
	saved_scale = 0.85;
	float height = WINDOW_HEIGHT * 0.05; // épaisseur fixe 5% de la fenêtre

	while (i < 4)
	{
		center = WINDOW_WIDTH / 2;
		track[i].left.x = center - (WINDOW_WIDTH / 12);
		track[i].right.x = center + (WINDOW_WIDTH / 12);

		center = WINDOW_HEIGHT * saved_scale;
		saved_scale = saved_scale - 0.10;
		printf("saved_scale= %f\n", saved_scale);

		track[i].left.y = center - (height / 2);
		track[i].right.y = center + (height / 2);

		i++;
	}
}

void	load_title_dimensions(t_track track[5])
{
	int center;
	
	center = WINDOW_WIDTH / 2;
	track[0].left.x = center - (WINDOW_WIDTH / 6);
	track[0].right.x = center + (WINDOW_WIDTH / 6);

	center = WINDOW_HEIGHT / 4;
	track[0].left.y = center - (WINDOW_HEIGHT / 8);
	track[0].right.y = center + (WINDOW_HEIGHT / 8);
	return;
}

void load_menu_texture(t_data *data)
{
    int width;
    int height;

    data->pannel_img[1] = mlx_xpm_file_to_image(data->mlx, "textures/pannels/menu.xpm", &width, &height);
    if (!data->pannel_img[1])
    {
        fprintf(stderr, "Failed to load pannel image 1\n");
        exit(EXIT_FAILURE);
    }
    data->pannel_img[2] = mlx_xpm_file_to_image(data->mlx, "textures/pannels/menu.xpm", &width, &height);
    if (!data->pannel_img[2])
    {
        fprintf(stderr, "Failed to load pannel image 2\n");
        exit(EXIT_FAILURE);
    }
    data->pannel_img[3] = mlx_xpm_file_to_image(data->mlx, "textures/pannels/menu.xpm", &width, &height);
    if (!data->pannel_img[3])
    {
        fprintf(stderr, "Failed to load pannel image 3\n");
        exit(EXIT_FAILURE);
    }
}


void display_menu(t_data *data)
{
    t_track track[5];

    load_pannel_dimensions(track);
    load_title_dimensions(track);
    load_menu_texture(data);

    int i = 1;
    while (i < 4)
    {
        mlx_put_image_to_window(data->mlx, data->win,
            data->pannel_img[i], track[i].left.x + ((track[i].right.x - track[i].left.x) * 0.5), 
			track[i].left.y + ((track[i].right.y - track[i].left.y) * 0.5));
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

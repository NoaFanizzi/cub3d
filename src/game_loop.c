#include "cube.h"

int rgb_to_color(int rgb[3])
{
    return (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

long long get_time_micro(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000LL + tv.tv_usec);
}

void limit_fps(t_game *game)
{
    long long now = get_time_micro();
    long long elapsed = now - game->last_frame;

    if (elapsed < FRAME_TIME_US)
        usleep(FRAME_TIME_US - elapsed);
}

void	color_ceiling_floor(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT / 2)
	{
		game->mlx_cfg.addr[i] = rgb_to_color(game->cfg.ceiling);
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		game->mlx_cfg.addr[i] = rgb_to_color(game->cfg.floor);
		i++;
	}
}

int	game_loop(t_game *game)
{

	limit_fps(game);
	player_movement(&game->player, game->cfg.map);
	color_ceiling_floor(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx_cfg.mlx, game->mlx_cfg.win, game->mlx_cfg.img, 0, 0);
	return (0);
}

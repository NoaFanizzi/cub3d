#include "cube.h"



int	game_loop(t_game *game)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
        game->mlx_cfg.addr[i] = 0x333333;

	raycasting(game);
	mlx_put_image_to_window(game->mlx_cfg.mlx, game->mlx_cfg.win, game->mlx_cfg.img, 0, 0);
	return (0);
}

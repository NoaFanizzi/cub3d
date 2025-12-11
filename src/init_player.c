#include "cube.h"

//find the start pos of the player and init his facing direction
static void	player_start_pos(char **map, t_config *config, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' ||
				map[i][j] == 'E' || map[i][j] == 'S')
			{
				config->player_start_dir = map[i][j];
				config->player_start_x = j;
				config->player_start_y = i;
				player->x = (double)j + 0.5;
				player->y = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
}

static void	player_facing_dir(t_game *game)
{
	if (game->cfg.player_start_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	if (game->cfg.player_start_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	if (game->cfg.player_start_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	if (game->cfg.player_start_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
}

static void	player_plane_dir(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (game->cfg.player_start_dir == 'N')
	{
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (game->cfg.player_start_dir == 'S')
	{
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (game->cfg.player_start_dir == 'W')
	{
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
	else if (game->cfg.player_start_dir == 'E')
	{
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
}

int	init_player(t_game *game)
{
	player_start_pos(game->cfg.map, &game->cfg, &game->player);
	player_facing_dir(game);
	player_plane_dir(game);
	game->player.rot_speed = 0.05;
	game->player.move_speed = 0.05;
	game->player.up = false;
	game->player.down = false;
	game->player.right = false;
	game->player.left = false;
	game->player.arrow_r = false;
	game->player.arrow_l = false;
	return (1);
}

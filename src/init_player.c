#include "cube.h"

void	player_start_pos(char **map, t_config *config, t_player *player)
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
				player->x = (double)j;
				player->y = (double)i;
			}
			j++;
		}
		i++;
	}
}

int	init_player(t_game *game)
{
	player_start_pos(game->cfg.map, &game->cfg, &game->player);
	printf("player.pos = {%f, %f}\n", game->player.x, game->player.y);
	return (1);
}

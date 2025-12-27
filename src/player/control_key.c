/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:24:49 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/27 11:43:45 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESCAPE)
		clean_game(game);
	if (keycode == W)
		game->player.up = true;
	if (keycode == S)
		game->player.down = true;
	if (keycode == D)
		game->player.right = true;
	if (keycode == A)
		game->player.left = true;
	if (keycode == RIGHT)
		game->player.arrow_r = true;
	if (keycode == LEFT)
		game->player.arrow_l = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.up = false;
	if (keycode == S)
		game->player.down = false;
	if (keycode == D)
		game->player.right = false;
	if (keycode == A)
		game->player.left = false;
	if (keycode == RIGHT)
		game->player.arrow_r = false;
	if (keycode == LEFT)
		game->player.arrow_l = false;
	return (0);
}

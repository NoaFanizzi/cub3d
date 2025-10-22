#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "parsing.h"
#include "struct.h"
#include "drawing.h"
#include "raycast.h"
#include "map.h"
#include "mlx.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 144
#define FOV 100

#define PI 3.14159265359

//AZERTY

#define W 122
#define A 113
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363


//QWERTY

// #define W 119
// #define A 97
// #define S 115
// #define D 100
// #define LEFT 65361
// #define RIGHT 65363

//main.c
void	display_tab(char **map);
void	display_menu(t_data *data);

//game.c
void	init_game(t_data *data);
int	    game_loop(t_data *data);

//mlx_utils.c
int	    close_window(t_data *data);
void	my_put_pixel(t_vec2 pos, int color, t_data *data);
void	draw_square(t_vec2 pos, int size, int color, t_data *data);

//player_movement.c
void	player_movement(t_player *player, t_data *data);
int	    key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);

//clean
void    clean_texture(t_data *data);
void    wipe(char **str);
void	free_tab(char ***tab);

#endif
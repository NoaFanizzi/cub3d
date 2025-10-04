#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "parsing.h"
#include "mlx.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 30
#define FOV 60

#define PI 3.14159265359

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363

void	my_put_pixel(t_vec2 pos, int color, t_data *data);
void	draw_square(t_vec2 pos, int size, int color, t_data *data);

int	    key_press(int keycode, t_player *player);
int	    key_release(int keycode, t_player *player);
void	player_movement(t_player *player);

int	close_window(t_data *data);
long	get_time_ms(void);


void	free_tab(char ***tab);
void	display_tab(char **map);

#endif
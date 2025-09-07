#ifndef CUB3D_H
#define CUB3D_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include "parsing.h"
#include "mlx.h"
#include <stdlib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define TILE_SIZE 50

int windows_creation(t_data *data);

void	free_tab(char ***tab);
void	display_tab(char **map);

#endif
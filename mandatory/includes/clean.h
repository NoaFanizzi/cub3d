#ifndef CLEAN_H
#define CLEAN_H

#include <unistd.h>
#include <stdlib.h>
#include "cub3d.h"
#include "struct.h"

void	free_tab(char ***tab);
void    wipe(char **str);
void    clean_texture(t_data *data);

#endif
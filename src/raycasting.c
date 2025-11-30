#include "cube.h"
#include <math.h>

void	init_ray_step_side(t_game *g)
{
	if (g->ray.dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_x = (g->player.x - g->ray.map_x) * g->ray.delta_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_x = (g->ray.map_x + 1.0 - g->player.x) * g->ray.delta_x;
	}
	if (g->ray.dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_y = (g->player.y - g->ray.map_y) * g->ray.delta_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_y = (g->ray.map_y + 1.0 - g->player.y) * g->ray.delta_y;
	}
}

void	init_ray(t_game *g, int x)
{
	g->ray.hit = 0;
	g->ray.side = 0;
	g->ray.camera_x = 2 * x / (double) WIDTH - 1;
	g->ray.dir_x = g->player.dir_x + g->player.plane_x * g->ray.camera_x;
	g->ray.dir_y = g->player.dir_y + g->player.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)g->player.x;
	g->ray.map_y = (int)g->player.y;
	if (g->ray.dir_x == 0)
		g->ray.delta_x = 1e30;
	else
		g->ray.delta_x = fabs(1 / g->ray.dir_x);
	if (g->ray.dir_y == 0)
		g->ray.delta_y = 1e30;
	else
		g->ray.delta_y = fabs(1 / g->ray.dir_y);
	init_ray_step_side(g);
}

void	check_hit(t_game *g)
{
	while (!g->ray.hit)
	{
		if (g->ray.side_x < g->ray.side_y)
		{
			g->ray.side_x += g->ray.delta_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_y += g->ray.delta_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}

		if (g->cfg.map[g->ray.map_y][g->ray.map_x] == '1')
			g->ray.hit = 1;
	}
}

static void draw_vertical(t_game *g, int x, int start, int end, int color)
{
    if (start < 0) start = 0;
    if (end >= HEIGHT) end = HEIGHT - 1;

    for (int y = start; y < end; y++)
        g->mlx_cfg.addr[y * WIDTH + x] = color;
}

void raycasting(t_game *g)
{
    for (int x = 0; x < WIDTH; x++)
    {
        init_ray(g, x);
		check_hit(g);
        // 6) PERP DISTANCE
        if (g->ray.side == 0)
            g->ray.perp_dist = (g->ray.side_x - g->ray.delta_x);
        else
            g->ray.perp_dist = (g->ray.side_y - g->ray.delta_y);

        // 7) LINE HEIGHT
        g->ray.line_height = (int)(HEIGHT / g->ray.perp_dist);

        g->ray.draw_start = -g->ray.line_height / 2 + HEIGHT / 2;
        g->ray.draw_end = g->ray.line_height / 2 + HEIGHT / 2;

        // 8) DRAW WALL — simple color
        int color = (g->ray.side == 0 ? 0xFF0000 : 0x880000); // red / darker red

        draw_vertical(g, x, g->ray.draw_start, g->ray.draw_end, color);
    }
}

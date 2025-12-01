#include "cube.h"

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

/* static void draw_vertical(t_game *g, int x, int start, int end, int color)
{
    if (start < 0) start = 0;
    if (end >= HEIGHT) end = HEIGHT - 1;

    for (int y = start; y < end; y++)
        g->mlx_cfg.addr[y * WIDTH + x] = color;
}
 */
static t_bool	is_power_two(int n)
{
	return (n && !(n & (n - 1)));
}

void	draw_vertical_text(t_mlx *mlx, int x, t_ray *ray, t_tex *tex)
{
	int	y;

	ray->tex_step = (double)tex->height / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_height / 2.0) * ray->tex_step;
	if (ray->draw_start < 0)
	{
		ray->tex_pos += -ray->draw_start * ray->tex_step;
		ray->draw_start = 0;
	}
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
    {
		
		if (is_power_two(tex->height))
        	ray->tex_y = (int)ray->tex_pos & (tex->height - 1); 
		else
		{
			ray->tex_y = (int)ray->tex_pos;
			if (ray->tex_y >= tex->height)
				ray->tex_y = tex->height - 1;
		}
        ray->tex_pos += ray->tex_step;

        int color = ((int *)tex->addr)[ray->tex_y * tex->width + ray->tex_x];

        my_put_pixel(mlx, x, y, color);
		y++;
    }
}

t_tex *choose_tex(t_game *g)
{
    if (g->ray.side == 0) // vertical wall
    {
        if (g->ray.dir_x > 0)
            return (&g->tex[EA]); // EAST
        else
            return (&g->tex[WE]); // WEST
    }
    else
    {
        if (g->ray.dir_y > 0)
            return (&g->tex[SO]); // SOUTH
        else
            return (&g->tex[NO]); // NORTH
    }
}

void	find_texture_x(t_ray *ray, t_player *p, t_tex *tex)
{
	if (ray->side == 0)
		ray->wall_x = p->y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = p->x + ray->perp_dist * ray->dir_x;

	ray->wall_x -= floor(ray->wall_x); // normalisation

	// 2) Convertir en coordonnée texture
	ray->tex_x = (int)(ray->wall_x * tex->width);

	// 3) Inverser selon le côté du mur
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

void raycasting(t_game *g)
{
	t_tex	*tex;

    for (int x = 0; x < WIDTH; x++)
    {
        init_ray(g, x);
		check_hit(g);
        if (g->ray.side == 0)
            g->ray.perp_dist = (g->ray.side_x - g->ray.delta_x);
        else
            g->ray.perp_dist = (g->ray.side_y - g->ray.delta_y);
        g->ray.line_height = (int)(HEIGHT / g->ray.perp_dist);
        g->ray.draw_start = -g->ray.line_height / 2 + HEIGHT / 2;
        g->ray.draw_end = g->ray.line_height / 2 + HEIGHT / 2;
		tex = choose_tex(g);
		find_texture_x(&g->ray, &g->player, tex);
		draw_vertical_text(&g->mlx_cfg, x, &g->ray, tex);
		// remplacer
/*         int color = (g->ray.side == 0 ? 0xFF0000 : 0x880000); // red / darker red

       draw_vertical(g, x, g->ray.draw_start, g->ray.draw_end, color); */
    }
}

#include "cube.h"

static t_bool	is_power_two(int n)
{
	return (n && !(n & (n - 1)));
}

t_tex	*choose_tex(t_game *g)
{
    if (g->ray.side == 0)
    {
        if (g->ray.dir_x > 0)
            return (&g->tex[EA]);
        else
            return (&g->tex[WE]);
    }
    else
    {
        if (g->ray.dir_y > 0)
            return (&g->tex[SO]);
        else
            return (&g->tex[NO]);
    }
}

void	find_texture_x(t_ray *ray, t_player *p, t_tex *tex)
{
	if (ray->side == 0)
		ray->wall_x = p->y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = p->x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x); // normalisation
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

void	find_texture_step(t_ray *ray, t_tex *tex)
{
	ray->tex_step = (double)tex->height / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_height / 2.0) * ray->tex_step;
	if (ray->draw_start < 0)
	{
		ray->tex_pos += -ray->draw_start * ray->tex_step;
		ray->draw_start = 0;
	}
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	draw_vertical_text(t_mlx *mlx, int x, t_ray *ray, t_tex *tex)
{
	int	y;

	find_texture_step(ray, tex);
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

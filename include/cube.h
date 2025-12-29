/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:57:31 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/29 11:57:34 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "mlx.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <fcntl.h>
# include <math.h>
# include <sys/stat.h>
# include <sys/time.h>

// window
# define WIDTH 1920
# define HEIGHT 1080

// FPS
# define TARGET_FPS 60

// keys
# define CROSS 17
# define ESCAPE 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

// textures
# define NB_TEXTURES 4

enum
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_mlx
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

// 'N', 'S', 'E', 'W'
typedef struct s_config
{
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;

	int			floor[3];
	int			ceiling[3];

	char		**map;
	int			map_width;
	int			map_height;

	int			player_start_x;
	int			player_start_y;
	char		player_start_dir;
}				t_config;

typedef struct s_player
{
	double		x;
	double		y;

	double		dir_x;
	double		dir_y;

	double		plane_x;
	double		plane_y;

	double		move_speed;
	double		rot_speed;

	t_bool		up;
	t_bool		down;
	t_bool		right;
	t_bool		left;

	t_bool		arrow_r;
	t_bool		arrow_l;
}				t_player;

typedef struct s_tex
{
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	char		*path;
}				t_tex;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;

	int			map_x;
	int			map_y;

	double		side_x;
	double		side_y;

	double		delta_x;
	double		delta_y;

	int			step_x;
	int			step_y;

	int			hit;
	int			side;

	double		perp_dist;

	int			line_height;
	int			draw_start;
	int			draw_end;

	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			index;

	double		tex_step;
	double		tex_pos;
}				t_ray;

// 0=NO, 1=SO, 2=WE, 3=EA
typedef struct s_game
{
	t_mlx		mlx_cfg;
	t_config	cfg;
	t_player	player;
	t_tex		tex[4];
	t_ray		ray;

	long		last_frame;
}				t_game;

// clean.c
void			remove_last_char(char *str);
void			free_tab(char ***tab);
void			ft_wipe(char **str);
void			clean_texture(t_config *config);
int				clean_game(t_game *game);

#endif
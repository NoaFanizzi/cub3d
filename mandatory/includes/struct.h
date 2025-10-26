#ifndef STRUCT_H
# define STRUCT_H

#define NB_TEXTURES 4

enum {
    NO = 0,
    SO = 1,
    WE = 2,
    EA = 3
};

typedef struct	s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct	s_vec2f
{
	double	x;
	double	y;
}				t_vec2f;

typedef struct s_player
{
	t_vec2f	pos;
	t_vec2f	dir;
	double	angle;
	double	rot_speed;
	int		speed;
	t_bool	key_up;
	t_bool	key_down;
	t_bool	key_left;
	t_bool	key_right;
	t_bool	left_rot;
	t_bool	right_rot;
}			t_player;

typedef struct s_texture
{
    void    *img;
    int     *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
	char 	*path;
}   		t_texture;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
	int		tile_size;
	long	last_frame;
	void *pannel_img[4];
	t_player player;
	t_texture   texture[NB_TEXTURES];
	t_vec2 tp_pos;
}			t_data;

typedef struct s_size
{
	size_t	x;
	size_t	y;
}			t_size;

typedef struct s_ray
{
	double	cos_angle;
	double	sin_angle;
	int		map_x;
	int		map_y;
}	t_ray;

typedef struct s_dda {
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int side;
    int hit;
} t_dda;

typedef struct s_wall
{
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}	t_wall;

typedef struct s_tex
{
	t_texture	*tex;
	int			tex_x;
	double		step;
	double		tex_pos;
}	t_tex;


typedef struct s_track
{
	t_vec2 left;
	t_vec2 right;
}				t_track;

typedef struct s_launch
{
	t_bool is_launched;
	t_data *data;
	t_track track;
}				t_launch;

#endif
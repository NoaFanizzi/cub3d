#ifndef STRUCT_H
# define STRUCT_H

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
	t_player player;
}			t_data;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
}				t_texture;

typedef struct s_size
{
	size_t	x;
	size_t	y;
}			t_size;

#endif
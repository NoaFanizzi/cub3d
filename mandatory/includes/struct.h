#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_player
{
	double	x;
	double y;
	double dir_x;
	double dir_y;
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
	t_player player;
}			t_data;

typedef struct s_size
{
	size_t	x;
	size_t	y;
}			t_size;

#endif
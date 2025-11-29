#ifndef CUBE_H
#define CUBE_H

typedef struct s_mlx {
    void    *mlx;
    void    *win;

    void    *img;        // image principale pour le rendu
    int     *addr;       // buffer pixels
    int     bpp;
    int     size_line;
    int     endian;
}   t_mlx;

typedef struct s_player {
    double  x;        // position en cases + décimales
    double  y;

    double  dir_x;    // direction du regard
    double  dir_y;

    double  plane_x;  // plan caméra (perpendiculaire)
    double  plane_y;

    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_game {
    t_mlx       mlx;
    t_config    cfg;
    t_player    player;
    t_tex       tex[4];   // 0=NO, 1=SO, 2=WE, 3=EA
    t_ray       ray;

    int         screen_w;
    int         screen_h;
}   t_game;

typedef struct s_tex {
    void    *img;       // image MLX
    int     width;      // largeur
    int     height;     // hauteur
    int     *data;      // pixels (addr)
    int     bpp;        // bits per pixel
    int     size_line;  // longueur d'une ligne de pixels
    int     endian;     // endianess
    char    *path;      // chemin du fichier xpm
}   t_tex;

typedef struct s_config {
    char    *tex_no;
    char    *tex_so;
    char    *tex_we;
    char    *tex_ea;

    int     floor[3];     // couleur F : R,G,B
    int     ceiling[3];   // couleur C : R,G,B

    char    **map;        // map brute
    int     map_width;    // largeur max
    int     map_height;   // nombre de lignes

    int     player_start_x;
    int     player_start_y;
    char    player_start_dir;  // 'N', 'S', 'E', 'W'
}   t_config;

typedef struct s_ray {
    double  camera_x;     // coordonnée du rayon dans l'espace caméra (-1 à 1)
    double  dir_x;        // direction du rayon
    double  dir_y;

    int     map_x;        // case de départ
    int     map_y;

    double  side_dist_x;
    double  side_dist_y;

    double  delta_dist_x;
    double  delta_dist_y;

    int     step_x;
    int     step_y;

    int     hit;          // on a touché un mur ?
    int     side;         // 0 = x, 1 = y

    double  perp_wall_dist;

    int     line_height;
    int     draw_start;
    int     draw_end;

    double  wall_x;       // position du point d’impact sur la texture
    int     tex_x;
    int     tex_y;

    double  tex_step;
    double  tex_pos;
}   t_ray;


#endif
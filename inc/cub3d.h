#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

// Window
# define WIN_W		1280
# define WIN_H		720
# define WIN_TITLE	"cub3D"
# define TILE		128

// Map characters
# define WALL		'1'
# define EMPTY		'0'
# define PLAYER_N	'N'
# define PLAYER_S	'S'
# define PLAYER_E	'E'
# define PLAYER_W	'W'

//Keyboard Keys
# define ESC		65307
# define LEFT_ARR	65361
# define RIGHT_ARR	65363

// Movement
# define MOVE_SPEED	0.05
# define ROT_SPEED	0.03

// Structs

// esta estrutura e para tratar das imagens e renderizaçao
typedef struct s_img
{
	void		*img;
	char		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

// esta estrutura e para tratar das texturas e cores
typedef struct s_textures
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	int		floor_color;
	int		ceiling_color;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
}	t_textures;

// esta estrutura trata da posiçao e orientaçao do jogador
typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;


// esta estrutura trata do mapa
typedef struct s_map
{
	char		**grid;
	int		width;
	int		height;
}	t_map;

// master struct, conseguimos aceder a todas as outras a partir desta
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_textures	textures;
	t_player	player;
	t_map		map;
}	t_game;


//Data init
int init_data(t_game *game);
void init_image(t_img *screen);



//First render test
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int render_loop(t_game *game);
void find_player(t_game *game);
int key_press(int keycode, t_game *game);


//raycast tests
void cast_ray(t_game *game, double camera_x);


#endif
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

// Window
# define WIN_W		1280
# define WIN_H		720
# define WIN_TITLE	"cub3D"

// Map characters
# define WALL		'1'
# define EMPTY		'0'
# define PLAYER_N	'N'
# define PLAYER_S	'S'
# define PLAYER_E	'E'
# define PLAYER_W	'W'

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
	int		height
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

#endif

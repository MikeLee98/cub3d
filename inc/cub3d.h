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
# define MOVE_SPEED	0.1
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
	int			f[3];
	int 		c[3];
	int     	floor_color;
	int     	ceiling_color;
	char		*str_f;
	char		*str_c;
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
	double	camera_x; //X coordinate on the camera plane, between [-1,1], -1 = left, 0 = middle, 1 = right, used to calc the direction of the ray
	double	dir_x;  //X coordinate of the ray, direction = player direction + plane * camera
	double	dir_y;  //same deal but for Y coordinate
	int		map_x;  //int of the player current X coordinate (used to represent the current GRID of the map the player is on, hence the integer)
	int		map_y;  //same deal but for Y coordinate
	int		step_x; //Will indicate the direction we're stepping, if it's a negative X direction, it will be -1, positive will be 1
	int		step_y; //same deal but for Y direction
	double 	perp_dist; //used to calculate the lenght of the ray(from it's starting position until it hits a wall)
	double	side_dist_x; //distance the ray has to travel from it's starting position to hit closest X side
	double	side_dist_y; //same deal but for Y
	double	delta_dist_x; //distance the ray has to travel to go from one X side to the next
	double	delta_dist_y; //same deal but for Y
	double	wall_x; //exact point wall hit
	int		tex_x;  //coordinate X of the texture
	int		tex_y;
	double	step; //how much to increase the texture coordinate per screen pixel
	int		side; //used to indicate what type of wall we hit (N/S OR E/W)
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;


// esta estrutura trata do mapa
typedef struct s_map
{
	char		**lines;
	char		**grid;
	int			width;
	int			height;
	int			start_index;
	int			player_x;
	int			player_y;
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
void init_player(t_player *player);





//First render test
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int render_loop(t_game *game);
void find_player(t_game *game);
int key_press(int keycode, t_game *game);


//raycast tests
void cast_ray(t_game *game, double camera_x);

// PARSING

// parsing.c
int parse(t_game *game, char *path);

// helper.c
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int error(char *message);
char **copy_grid(t_map *map);
void free_split(char **split);

// check_extension.c
int check_file(char *path);
int check_extension(char *path);

// read_file.c
char **read_lines(t_map *map, int fd);
int read_file(t_map *map, char *path);

// parse_elements.c
int check_colors(t_game *game, char *trimmed);
int parse_element(t_game *game, char *line);
int parse_elements(t_game *game);

// validation.c
int validate_values(t_game *game);

// parse_map.c
int parse_map(t_map *map);

// validate_map.c
int validate_map(t_map *map);


//testing
int load_textures(t_game *game);
void render_3d(t_game *g);
void find_player(t_game *game);

void init_ray_delta(t_game *game, t_ray *ray, int x);
void init_ray_step(t_game *game, t_ray *ray);

void dda_loop(t_game *game, t_ray *ray);
void	set_perp_dist(t_ray *ray);
void dda(t_game *game, t_ray *ray);
void draw_line_distance(t_ray *ray);
double get_texture_position(t_game *game, t_ray *ray, t_img *tex);

void	free_mlx(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:26:39 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 21:18:18 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	int			f[3];
	int			c[3];
	int			floor_color;
	int			ceiling_color;
	char		*str_f;
	char		*str_c;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
}	t_textures;

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
	double	perp_dist;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_map
{
	char	**lines;
	char	**grid;
	int		width;
	int		height;
	int		start_index;
	int		player_x;
	int		player_y;
}	t_map;

// master struct
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_textures	textures;
	t_player	player;
	t_map		map;
}	t_game;

//First render test
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		render_loop(t_game *game);
int		key_press(int keycode, t_game *game);

// movement.c
int		key_press(int keycode, t_game *game);

// moves.c
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);

//camera.c
void	rotate(t_game *game, double angle);

// find_player.c
void	find_player(t_game *game);

//raycast tests
void	cast_ray(t_game *game, double camera_x);

// parsing.c
int		parse(t_game *game, char *path);

// helper.c
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		error(char *message, t_game *game);
char	**copy_grid(t_map *map);
void	free_split(char **split);

// check_extension.c
int		check_file(char *path, t_game *game);
int		check_extension(char *path, t_game *game);

// read_file.c
char	**read_lines(t_map *map, int fd);
int		read_file(t_map *map, char *path, t_game *game);

// parse_elements.c
int		parse_elements(t_game *game);

// validation.c
int		validate_values(t_game *game);

// parse_map.c
int		parse_map(t_map *map, t_game *game);

// validate_map.c
int		validate_map(t_map *map, t_game *game);

//testing
int		load_textures(t_game *game);
void	render_3d(t_game *g);

void	init_ray_delta(t_game *game, t_ray *ray, int x);
void	init_ray_step(t_game *game, t_ray *ray);

void	dda_loop(t_game *game, t_ray *ray);
void	set_perp_dist(t_ray *ray);
void	dda(t_game *game, t_ray *ray);
void	draw_line_distance(t_ray *ray);
double	get_texture_position(t_game *game, t_ray *ray, t_img *tex);
int		get_texture_pixel(t_img *texture, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

void	free_mlx(t_game *game);
void	free_parsing(t_game *game);
void	free_game(t_game *game);
int		close_window(t_game *game);

#endif

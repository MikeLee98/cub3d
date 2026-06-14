#include "../../inc/cub3d.h"

int load_textures(t_game *game)
{
	t_textures *t;

	t = &game->textures;
	t->no.img = mlx_xpm_file_to_image(game->mlx, t->path_no, &t->no.width, &t->no.height);
	t->so.img = mlx_xpm_file_to_image(game->mlx, t->path_so, &t->so.width, &t->so.height);
	t->we.img = mlx_xpm_file_to_image(game->mlx, t->path_we, &t->we.width, &t->we.height);
	t->ea.img = mlx_xpm_file_to_image(game->mlx, t->path_ea, &t->ea.width, &t->ea.height);
	if (!t->no.img || !t->so.img || !t->we.img || !t->ea.img)
		return (error("failed to load texture"), 1);
	t->no.addr = mlx_get_data_addr(t->no.img, &t->no.bpp, &t->no.line_len, &t->no.endian);
	t->so.addr = mlx_get_data_addr(t->so.img, &t->so.bpp, &t->so.line_len, &t->so.endian);
	t->we.addr = mlx_get_data_addr(t->we.img, &t->we.bpp, &t->we.line_len, &t->we.endian);
	t->ea.addr = mlx_get_data_addr(t->ea.img, &t->ea.bpp, &t->ea.line_len, &t->ea.endian);
	t->floor_color = t->f[0] << 16 | t->f[1] << 8 | t->f[2];
	t->ceiling_color = t->c[0] << 16 | t->c[1] << 8 | t->c[2];
	return (0);
}

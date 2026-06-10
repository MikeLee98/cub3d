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
    t->floor_color = t->f[0] << 16 | t->f[1] << 8 | t->f[2];
    t->ceiling_color = t->c[0] << 16 | t->c[1] << 8 | t->c[2];
    return (0);
}

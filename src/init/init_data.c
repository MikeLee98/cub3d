#include "cub3d.h"

void init_image(t_img *screen)
{
    screen->img = NULL;
	screen->addr = NULL;
	screen->bpp = 0;
	screen->line_len = 0;
	screen->endian = 0;
	screen->width = 0;
	screen->height = 0;
}


void init_textures(t_textures *textures)
{
    //t_img		no; think abt this later
	//t_img		so;
	//t_img		we;
	//t_img		ea;
	textures->floor_color = 0;
	textures->ceiling_color = 0;
	textures->path_no = NULL;
	textures->path_so = NULL;
	textures->path_we = NULL;
	textures->path_ea = NULL;
}


void init_player(t_player *player)
{
    player->x = 0;
    player->y = 0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0;
}

/*void init_map(t_map *map)
{
    static char *map1[] = {
    "111111",
    "100N01",
    "101001",
    "100001",
    "111111",
    NULL
};
    map->grid = map1;
    map->width = 6;
    map->height = 5;
}
    */


/*int init_data(t_game *game)
{
    game->mlx = NULL;
    game->win = NULL;

    game->mlx = mlx_init();
    if (!game->mlx)
        return (1);

    game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_TITLE);
    if (!game->win)
        return (1);

    init_image(&game->screen);
    init_player(&game->player);
    init_textures(&game->textures);
    //init_map(&game->map);
    find_player(game);

    

    return (0);

}
    */
#include "cub3d.h"


int init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error("mlx init failed"), 1);
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
	if (!game->win)
		return (error("window creation failed"), 1);
    
    init_image(&game->screen);
    init_player(&game->player);
    find_player(game);

  
	if (load_textures(game))
		return (1);

	return (0);
}

int loop(t_game *game)
{
    //render_3d(game);
    render_loop(game);
    return (0);
}



int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        printf("Usage: ./cub3D <map_file.cub>\n");
        return (1);
    }

    ft_memset(&game, 0, sizeof(t_game));

    if (parse(&game, argv[1]))
        return (1);

    if (init_game(&game))
        return (1);

    printf("map is valid\n");

   
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_loop_hook(game.mlx, loop, &game);
    mlx_loop(game.mlx);

    

    return (0);
}
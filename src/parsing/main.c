#include "../../inc/cub3d.h"

int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (error("mlx init failed"), 1);
    game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
    if (!game->win)
        return (error("window creation failed"), 1);
    if (load_textures(game))
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (parse(&game, argv[1]))
        return (1);
	if (init_game(&game))
		return (1);
	printf("map is valid\n");
	return (0);
}

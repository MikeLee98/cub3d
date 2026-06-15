#include "cub3d.h"

void	free_mlx(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_image(game->mlx, game->textures.so.img);
		mlx_destroy_image(game->mlx, game->textures.no.img);
		mlx_destroy_image(game->mlx, game->textures.we.img);
		mlx_destroy_image(game->mlx, game->textures.ea.img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

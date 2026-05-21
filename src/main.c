#include "cub3d.h"

int loop(t_game *game)
{
    render_loop(game);
    return (0);
}

int main(void)
{
    t_game game;

    if (init_data(&game))
        return (1);
        
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_loop_hook(game.mlx, loop, &game);
    mlx_loop(game.mlx);
    return (0);
}
#include "cub3d.h"

int is_wall(t_game *game, double x, double y)
{
    if (game->map.grid[(int)y][(int)x] == '1')
        return (1);
    return (0);
}

void move_forward(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
    new_y = game->player.y + game->player.dir_y * MOVE_SPEED;

    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

void move_backward(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
    new_y = game->player.y - game->player.dir_y * MOVE_SPEED;

    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

void strafe_left(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.x + game->player.dir_y * MOVE_SPEED;
    new_y = game->player.y - game->player.dir_x * MOVE_SPEED;

    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

void strafe_right(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.x - game->player.dir_y * MOVE_SPEED;
    new_y = game->player.y + game->player.dir_x * MOVE_SPEED;

    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

void rotate(t_game *game, double angle)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;

    game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);

    game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == ESC) 
        exit(0);

    if (keycode == 'w')
        move_forward(game);
    if (keycode == 's')
        move_backward(game);
    if (keycode == 'a')
        strafe_left(game);
    if (keycode == 'd')
        strafe_right(game);
    if (keycode == LEFT_ARR) 
        rotate(game, -ROT_SPEED);
    if (keycode == RIGHT_ARR) 
        rotate(game, ROT_SPEED);

    return (0);
}
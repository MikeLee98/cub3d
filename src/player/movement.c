#include  "cub3d.h"

int is_wall(t_game *game, double x, double y)
{
    if (y < 0 || x < 0 || y >= game->map.height)
        return 1;
    if (x >= (int)strlen(game->map.grid[(int)y]))
        return 1;

    if (game->map.grid[(int)y][(int)x] == '1')
        return 1;

    return 0;
}

void find_player(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            char c = game->map.grid[y][x];

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->player.x = x + 0.5;
                game->player.y = y + 0.5;
                game->player.dir_x = 0;
                game->player.dir_y = 0;
                game->player.plane_x = 0;
                game->player.plane_y = 0;

                if (c == 'N')
                {
                    game->player.dir_y = -1;
                    game->player.plane_x = 0.66;
                }
                else if (c == 'S')
                {
                    game->player.dir_y = 1;
                    game->player.plane_x = -0.66;
                }
                else if (c == 'E')
                {
                    game->player.dir_x = 1;
                    game->player.plane_y = 0.66;
                }
                else if (c == 'W')
                {
                    game->player.dir_x = -1;
                    game->player.plane_y = -0.66;
                }
                game->map.grid[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
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
    {
        free_game(game);
        exit(0);
    }
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
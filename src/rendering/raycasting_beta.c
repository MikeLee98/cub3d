#include "cub3d.h"



void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx;
    int sy;

    if (x0 < x1)
        sx = 1;
    else
        sx = -1;

    if (y0 < y1)
        sy = 1;
    else
        sy = -1;


    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(&game->screen, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void cast_ray(t_game *game, double camera_x)
{
    t_ray ray;


    ray.map_x = (int)game->player.x;
    ray.map_y = (int)game->player.y;

    ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;

    ray.deltadist_x = fabs(1 / ray.dir_x);
    ray.deltadist_y = fabs(1 / ray.dir_y);

    if (ray.dir_x < 0)
    {
        ray.step_x = -1;
        ray.sidedist_x = (game->player.x - ray.map_x) * ray.deltadist_x;
    }
    else
    {
        ray.step_x = 1;
        ray.sidedist_x = (ray.map_x + 1.0 - game->player.x) * ray.deltadist_x;
    }

    if (ray.dir_y < 0)
    {
        ray.step_y = -1;
        ray.sidedist_y = (game->player.y - ray.map_y) * ray.deltadist_y;
    }
    else
    {
        ray.step_y = 1;
        ray.sidedist_y = (ray.map_y + 1.0 - game->player.y) * ray.deltadist_y;
    }

    
    while (1)
    {
        if (ray.sidedist_x < ray.sidedist_y)
        {
            ray.sidedist_x += ray.deltadist_x;
            ray.map_x += ray.step_x;
            ray.side = 0;
        }
        else
        {
            ray.sidedist_y += ray.deltadist_y;
            ray.map_y += ray.step_y;
            ray.side = 1;
        }

        if (game->map.grid[ray.map_y][ray.map_x] == '1')
            break;
    }
    double perp_dist;

    if (ray.side == 0)
        perp_dist = (ray.map_x - game->player.x + (1 - ray.step_x) / 2) / ray.dir_x;
    else
        perp_dist = (ray.map_y - game->player.y + (1 - ray.step_y) / 2) / ray.dir_y;

    double hit_x = game->player.x + ray.dir_x * perp_dist;
    double hit_y = game->player.y + ray.dir_y * perp_dist;

  
    draw_line(game,(game->player.x )* TILE,(game->player.y)* TILE, hit_x * TILE, hit_y * TILE, 0x00FF00);

    
}
#include "cub3d.h"





void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE)
    {
        j = 0;
        while (j < TILE)
        {
            my_mlx_pixel_put(&game->screen, x * TILE + i, y * TILE + j, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (game->map.grid[y])
    {
        x = 0;
        while (game->map.grid[y][x])
        {
            if (game->map.grid[y][x] == '1')
                draw_square(game, x, y, 0x000000); 
            
            else
                draw_square(game, x, y, 0xCCCCCC);
            x++;
        } 
        y++;
    }
    
}

void find_player(t_game *game) //temporary 
{
    int x;
    int y;

    y = 0;
    while (game->map.grid[y])
    {
        x = 0;
        while (game->map.grid[y][x])
        {
            if (game->map.grid[y][x] == 'N')
            {
                game->player.x = x  ;
                game->player.y = y  ;
                game->player.dir_x = 0;
                game->player.dir_y = -1;
                game->player.plane_x = 0.66;
		        game->player.plane_y = 0;
             
                return;
            }
            x++;
        }
        y++;
    }
}



void draw_player(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < TILE / 2)
    {
        j = 0;
        while (j < TILE / 2)
        {
            my_mlx_pixel_put(&game->screen, game->player.x * TILE + i, game->player.y * TILE + j, 0xFF0000); 
            j++;
        }
        i++;
    }
}

int render_loop(t_game *game)
{
    int x = 0;

    game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!game->screen.img)
        return (1);

    game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp, &game->screen.line_len, &game->screen.endian);

    if (!game->map.grid)
        return (printf("ERROR: map is NULL\n"), 1);

    draw_map(game);
    draw_player(game);

    while (x < WIN_W)
    {
        double camera_x = 2 * x / (double)WIN_W - 1;

        cast_ray(game, camera_x);
        x++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    mlx_destroy_image(game->mlx, game->screen.img);

    return (0);
}
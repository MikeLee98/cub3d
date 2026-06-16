#include "cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (!img || !img->addr)
        return;

    if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
        return;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

t_img *get_wall_texture(t_game *data, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->step_x > 0)
            return (&data->textures.ea);
        return (&data->textures.we);
    }
    if (ray->side == 1)
    {
        if (ray->step_y > 0)
            return (&data->textures.so);
        return (&data->textures.no);
    }
    return (0); //might have to change?
}

int get_texture_pixel(t_img *texture, int x, int y)
{
    char *pixel;

    pixel = texture->addr + (y * texture->line_len) + (x * (texture->bpp / 8));
    return (*(unsigned int *)pixel);
}

static void draw_column(t_game *game, t_ray *ray, int x)
{
    int y;
    double tex_pos;
    int color;
    t_img *tex;

    draw_line_distance(ray);
    tex = get_wall_texture(game, ray);
    tex_pos = get_texture_position(game, ray, tex);
    y = 0;
    while (y < ray->draw_start)
        my_mlx_pixel_put(&game->screen, x, y++, game->textures.ceiling_color);
    while (y <= ray->draw_end)
    {
        ray->tex_y = (int)tex_pos; //coordinate texture to integer
        if (ray->tex_y >= tex->height)
            ray->tex_y = tex->height - 1; //avoid overflow
        if (ray->tex_y < 0)
            ray->tex_y = 0;
        color = get_texture_pixel(tex, ray->tex_x, ray->tex_y);
        my_mlx_pixel_put(&game->screen, x, y++, color);
        tex_pos += ray->step;
    }
    while (y < WIN_H)
        my_mlx_pixel_put(&game->screen, x, y++, game->textures.floor_color);
}

void render_3d(t_game *game)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < WIN_W)
    {
        //printf("perp_dist = %f\n", ray.perp_dist);
        init_ray_delta(game, &ray, x);
        init_ray_step(game, &ray);
        dda_loop(game, &ray);
        draw_column(game, &ray, x);
        x++;
    }
}

int render_loop(t_game *game)
{
    game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    game->screen.addr = mlx_get_data_addr(game->screen.img,&game->screen.bpp,&game->screen.line_len, &game->screen.endian);

    render_3d(game);

    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    mlx_destroy_image(game->mlx, game->screen.img);

    return (0);
}
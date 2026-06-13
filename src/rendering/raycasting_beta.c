#include "cub3d.h"


/*
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

    
} */

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
            return (&data->textures.we);
        return (&data->textures.ea);
    }
    if (ray->step_y > 0)
        return (&data->textures.so);
    return (&data->textures.no);
}

int get_texture_pixel(t_img *texture, int x, int y)
{
    char *pixel;

    pixel = texture->addr + (y * texture->line_len) + (x * (texture->bpp / 8));
    return (*(unsigned int *)pixel);
}

/* static void init_ray(t_game *game, t_ray *ray, int x)
{
    
    float camera_x;

    camera_x = 2.0 * x / WIN_W - 1.0;

    ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;

    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;

    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1.0 / ray->dir_x);

    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->dir_y);

    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }

    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
} */

/* void perform_dda(t_game *game, t_ray *ray)
{
    int hit = 0;

    char c = game->map.grid[ray->map_y][ray->map_x];

    if (c == '1')
        hit = 1;
    else if (c == ' ' || c == '\0')
    {
        ray->perp_dist = 1000.0;
        return;
    }

    while (!hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x >= game->map.width)
            return;

        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }

    if (ray->side == 0) //avoids fucked angle
        ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;

    if (ray->perp_dist < 0.001)
        ray->perp_dist = 0.001;
} */

static void draw_column(t_game *game, t_ray *ray, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    int y;
    float step;
    float tex_pos;
    int tex_x;
    int tex_y;
    int color;
    t_img *tex;

    line_height = (int)(WIN_H / ray->perp_dist);

    draw_start = -line_height / 2 + WIN_H / 2;
    draw_end = line_height / 2 + WIN_H / 2;

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= WIN_H)
        draw_end = WIN_H - 1;

    tex = get_wall_texture(game, ray);

    float wall_x;
    if (ray->side == 0)
        wall_x = game->player.y + ray->perp_dist * ray->dir_y;
    else
        wall_x = game->player.x + ray->perp_dist * ray->dir_x;

    wall_x -= floor(wall_x);

    tex_x = (int)(wall_x * tex->width);

    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0)) tex_x = tex->width - tex_x - 1;

    step = (float)tex->height / line_height;
    tex_pos = (draw_start - WIN_H / 2 + line_height / 2) * step;

    y = 0;
    while (y < draw_start)
        my_mlx_pixel_put(&game->screen, x, y++, game->textures.ceiling_color);

    while (y <= draw_end)
    {
        tex_y = (int)tex_pos;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        if (tex_y < 0)
            tex_y = 0;

        color = get_texture_pixel(tex, tex_x, tex_y);
        my_mlx_pixel_put(&game->screen, x, y++, color);

        tex_pos += step;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_beta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:42:42 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/06/18 10:42:42 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_wall_texture(t_game *data, t_ray *ray)
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
	return (NULL);
}

static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	double	tex_pos;
	int		color;
	t_img	*tex;

	draw_line_distance(ray);
	tex = get_wall_texture(game, ray);
	tex_pos = get_texture_position(game, ray, tex);
	y = 0;
	while (y < ray->draw_start)
		my_mlx_pixel_put(&game->screen, x, y++, game->textures.ceiling_color);
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)tex_pos;
		if (ray->tex_y >= tex->height)
			ray->tex_y = tex->height - 1;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		color = get_texture_pixel(tex, ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&game->screen, x, y++, color);
		tex_pos += ray->step;
	}
	while (y < WIN_H)
		my_mlx_pixel_put(&game->screen, x, y++, game->textures.floor_color);
}

void	render_3d(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray_delta(game, &ray, x);
		init_ray_step(game, &ray);
		dda_loop(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}

int	render_loop(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	mlx_destroy_image(game->mlx, game->screen.img);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_map_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:42:19 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/06/18 10:42:19 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_distance(t_ray *ray)
{
	ray->line_height = (int)(WIN_H / ray->perp_dist);
	ray->draw_start = (ray->line_height * -1) / 2 + WIN_H / 2;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

double	get_texture_position(t_game *game, t_ray *ray, t_img *tex)
{
	double	tex_pos;

	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
	ray->step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2)
		* ray->step;
	return (tex_pos);
}

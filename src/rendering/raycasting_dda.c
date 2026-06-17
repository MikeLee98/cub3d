/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:47:19 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 12:47:19 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_game *game, t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
		ray->map_x = ray->map_x + ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
		ray->map_y = ray->map_y + ray->step_y;
		ray->side = 1;
	}
	if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.height
		|| ray->map_x >= game->map.width)
		return ;
}

void	set_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_dist < 0.001)
		ray->perp_dist = 0.001;
}

void	dda_loop(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		dda(game, ray);
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	set_perp_dist(ray);
}

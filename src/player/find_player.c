/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:33:00 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:33:27 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction(t_game *game, char c)
{
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
}

void	find_player(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				set_direction(game, c);
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

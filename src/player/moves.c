/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:33:58 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:35:59 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	if (y < 0 || x < 0 || y >= game->map.height)
		return (1);
	if (x >= (int)strlen(game->map.grid[(int)y]))
		return (1);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

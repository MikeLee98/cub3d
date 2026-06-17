/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:47:07 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 12:47:07 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:43:20 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/06/18 10:43:20 by jlopes-c         ###   ########.fr       */
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

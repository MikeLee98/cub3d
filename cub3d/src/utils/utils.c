/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:47:36 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:55:18 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->textures.no.img)
		mlx_destroy_image(game->mlx, game->textures.no.img);
	if (game->textures.so.img)
		mlx_destroy_image(game->mlx, game->textures.so.img);
	if (game->textures.we.img)
		mlx_destroy_image(game->mlx, game->textures.we.img);
	if (game->textures.ea.img)
		mlx_destroy_image(game->mlx, game->textures.ea.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	free_parsing(t_game *game)
{
	if (!game)
		return ;
	if (game->map.lines)
		free_split(game->map.lines);
	if (game->map.grid)
		free_split(game->map.grid);
	if (game->textures.str_f)
		free(game->textures.str_f);
	if (game->textures.str_c)
		free(game->textures.str_c);
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
}

void	free_game(t_game *game)
{
	free_parsing(game);
	free_mlx(game);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}

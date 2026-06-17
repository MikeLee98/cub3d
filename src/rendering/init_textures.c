/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:47:12 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:44:40 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one_texture(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

int	load_textures(t_game *game)
{
	t_textures	*t;

	t = &game->textures;
	if (load_one_texture(game, &t->no, t->path_no)
		|| load_one_texture(game, &t->so, t->path_so)
		|| load_one_texture(game, &t->we, t->path_we)
		|| load_one_texture(game, &t->ea, t->path_ea))
		return (1);
	t->floor_color = t->f[0] << 16 | t->f[1] << 8 | t->f[2];
	t->ceiling_color = t->c[0] << 16 | t->c[1] << 8 | t->c[2];
	return (0);
}

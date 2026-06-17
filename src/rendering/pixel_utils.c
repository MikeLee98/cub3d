/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:52:13 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:52:26 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// pixel_utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->line_len) + (x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

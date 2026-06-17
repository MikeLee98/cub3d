/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:46:37 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 12:59:12 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_map_width(t_map *map)
{
	int	i;
	int	j;

	i = map->start_index;
	j = 0;
	while (map->lines[i])
	{
		if (j < (int)ft_strlen(map->lines[i]))
			j = ft_strlen(map->lines[i]);
		i++;
	}
	return (j);
}

static int	fill_grid_row(t_map *map, int row)
{
	int	len;

	map->grid[row] = ft_calloc(map->width + 1, sizeof(char));
	if (!map->grid[row])
		return (1);
	len = ft_strlen(map->lines[map->start_index + row]);
	ft_memcpy(map->grid[row], map->lines[map->start_index + row], len);
	ft_memset(map->grid[row] + len, ' ', map->width - len);
	return (0);
}

int	parse_map(t_map *map, t_game *game)
{
	int	i;

	map->height = map->height - map->start_index;
	map->width = get_map_width(map);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (free_parsing(game), 1);
	i = 0;
	while (i < map->height)
	{
		if (fill_grid_row(map, i))
			return (free_parsing(game), 1);
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

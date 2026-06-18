/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 22:13:02 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 22:31:44 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	**create_visited_grid(t_map *map)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = malloc(sizeof(char) * map->width);
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			return (NULL);
		}
		ft_memset(visited[i], 0, map->width);
		i++;
	}
	return (visited);
}

static void	free_visited_grid(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static void	flood_fill(t_map *map, char **visited, int i, int j)
{
	if (i < 0 || i >= map->height || j < 0 || j >= map->width)
		return ;
	if (visited[i][j] || !ft_strchr("01NSEW", map->grid[i][j]))
		return ;
	visited[i][j] = 1;
	flood_fill(map, visited, i - 1, j);
	flood_fill(map, visited, i + 1, j);
	flood_fill(map, visited, i, j - 1);
	flood_fill(map, visited, i, j + 1);
}

int	validate_connected(t_map *map, t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = create_visited_grid(map);
	if (!visited)
		return (1);
	flood_fill(map, visited, map->player_y, map->player_x);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("01NSEW", map->grid[i][j]) && !visited[i][j])
			{
				free_visited_grid(visited, map->height);
				return (error("map has disconnected rooms", game), 1);
			}
			j++;
		}
		i++;
	}
	free_visited_grid(visited, map->height);
	return (0);
}

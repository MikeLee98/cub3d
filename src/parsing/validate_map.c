#include "../../inc/cub3d.h"

int validate_walls(t_map *map, t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("0NSEW", map->grid[i][j]))
			{
				if (i == 0 || i == map->height - 1
					|| j == 0 || j == map->width - 1)
					return (error("map is not closed", game), 1);
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
					|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
					return (error("map is not closed", game), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int validate_characters(t_map *map, t_game *game)
{
	int i;
	int j;
	int player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				player_count++;
				map->player_y = i;
				map->player_x = j;
			}
			else if (!ft_strchr("01 NSEW", map->grid[i][j]))
				return (error("invalid character in map", game), 1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (error("map must have exactly one player", game), 1);
	return (0);
}

int validate_map(t_map *map, t_game *game)
{
	if (validate_characters(map, game))
		return (1);
	if (validate_walls(map, game))
		return (1);
	return (0);
}

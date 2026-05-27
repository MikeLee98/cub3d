#include "../../inc/cub3d.h"

int flood_fill(char **grid, int y, int x, int height, int width)
{
    if (y < 0 || y >= height || x < 0 || x >= width)
        return (error("map is not closed"), 1);
    if (grid[y][x] == ' ')
        return (error("map is not closed"), 1);
    if (grid[y][x] == '1' || grid[y][x] == 'V')
        return (0);
    grid[y][x] = 'V';
    if (flood_fill(grid, y + 1, x, height, width))
        return (1);
    if (flood_fill(grid, y - 1, x, height, width))
        return (1);
    if (flood_fill(grid, y, x + 1, height, width))
        return (1);
    if (flood_fill(grid, y, x - 1, height, width))
        return (1);
    return (0);
}

int validate_characters(t_map *map)
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
				return (error("invalid character in map"), 1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (error("map must have exactly one player"), 1);
	return (0);
}

int validate_map(t_map *map)
{
    char    **copy;
    int     validation;

    if (validate_characters(map))
        return (1);
	copy = copy_grid(map);
	if (!copy)
		return (1);
	validation = flood_fill(copy, map->player_y, map->player_x, map->height, map->width);
    return (validation);
}

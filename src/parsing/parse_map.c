#include "../../inc/cub3d.h"

int parse_map(t_map *map)
{
	int i;
	int j;
	int len;

	i = map->start_index;
	j = 0;
	map->height = map->height - map->start_index;
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	while (map->lines[i])
	{
		if (j < ft_strlen(map->lines[i]))
			j = ft_strlen(map->lines[i]);
		i++;
	}
	map->width = j;
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_calloc(map->width + 1, sizeof(char));
		if (!map->grid[i])
			return(1);
		len = ft_strlen(map->lines[map->start_index + i]);
		ft_memcpy(map->grid[i], map->lines[map->start_index + i], len);
		ft_memset(map->grid[i] + len, ' ', map->width - len);
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

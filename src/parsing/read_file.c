#include "../../inc/cub3d.h"

char **read_lines(t_map *map, int fd)
{
    char **lines = NULL;
    char *line;
    int count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        lines = ft_realloc(lines, sizeof(char *) * count, sizeof(char *) * (count + 2));
        lines[count] = line;
        lines[count + 1] = NULL;
        count++;
    }
	map->height = count;
    return (lines);
}

int read_file(t_map *map, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file"));
	map->lines = read_lines(map, fd);
	close(fd);
	if (!map->lines)
		return (error("failed to read file"));
	return (0);
}

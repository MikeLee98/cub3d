#include "../../inc/cub3d.h"

char **read_lines(int fd)
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
    return (lines);
}

int read_file(t_game *game, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file"));
	game->map.map = read_lines(fd);
	close(fd);
	if (!game->map.map)
		return (error("failed to read file"));
	return (0);
}

int check_file(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (error("cannot open file"));
    close(fd);
    return (0);
}

int check_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4 || ft_strcmp(path + len - 4, ".cub") != 0)
		return (1);
	return (0);
}

int parse(t_game *game, char *path)
{
	if (check_extension(path) || check_file(path))
		return (error("invalid file extension"));
	if (read_file(game, path))
		return (1);
	if (parse_elements(game))
		return (1);
	if (parse_map(game))
		return (1);
	if (validate_map(game))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (parse(&game, argv[1]))
        return (1);
	return (0);
}

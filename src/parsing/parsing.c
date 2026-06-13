#include "../../inc/cub3d.h"

int parse(t_game *game, char *path)
{
	if (check_extension(path) || check_file(path))
		return (error("invalid file extension"), 1);
	if (read_file(&game->map, path))
		return (1);
	if (parse_elements(game))
		return (1);
	if (parse_map(&game->map))
		return (1);
	if (validate_map(&game->map))
		return (1);

	return (0);
}

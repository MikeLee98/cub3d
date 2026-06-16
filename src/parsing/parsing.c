#include "../../inc/cub3d.h"

int parse(t_game *game, char *path)
{
	if (check_extension(path, game) || check_file(path, game))
		return (1);
	if (read_file(&game->map, path, game))
		return (1);
	if (parse_elements(game))
		return (1);
	if (parse_map(&game->map, game))
		return (1);
	if (validate_map(&game->map, game))
		return (1);
	return (0);
}

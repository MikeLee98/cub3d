#include "../../inc/cub3d.h"

int	validate_color(char *str, int color[3])
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	if (!split)
		return (1);
	while (split[i])
		i++;
	if (i != 3)
		return (free_split(split), error("color not RGB format"), 1);
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(split[i]);
		if (color[i] < 0 || color[i] > 255)
			return (free_split(split), error("color not RGB format"), 1);
		i++;
	}
	free_split(split);
	return (0);
}

int	validate_path(char *path)
{
    size_t  len;
    int     fd;

    len = ft_strlen(path);
    if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
        return (error("texture must be a .xpm file"), 1);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (error("texture file not found"), 1);
    close(fd);
    return (0);
}

int validate_values(t_game *game)
{
	if (!game->textures.path_no || !game->textures.path_so || !game->textures.path_we
		|| !game->textures.path_ea || !game->textures.str_f || !game->textures.str_c)
		return (1);
	if (validate_path(game->textures.path_no) || validate_path(game->textures.path_so)
		|| validate_path(game->textures.path_we) || validate_path(game->textures.path_ea))
		return (1);
	if (validate_color(game->textures.str_f, game->textures.f) || validate_color(game->textures.str_c, game->textures.c))
		return (1);
	return (0);
}

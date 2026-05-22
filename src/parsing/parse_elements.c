#include "../../inc/cub3d.h"

int validate_values(game)
{
	
}

int parse_element(t_game *game, char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		game->textures.no = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "SO ", 3))
		game->textures.so = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "WE ", 3))
		game->textures.we = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "EA ", 3))
		game->textures.ea = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "F ", 2))
		game->textures.f = ft_strdup(str + 2);
	else if (!ft_strncmp(str, "C ", 2))
		game->textures.c = ft_strdup(str + 2);
	else
		return (free(str), 1);
	return (0);
}

int	parse_elements(t_game *game)
{
	int		i;
	char 	*line;

	i = 0;
	while (game->map.lines[i])
	{
		line = ft_strtrim(game->map.lines[i], " \t\n");
		if (!line)
			return (1);
		if (line[0] == '\0')
		{
			free(line);
			i++;
			continue;
		}
		if (parse_element(game, line))
    		break ;
		i++;
	}
	if (validate_values(game))
		return (error("missing element"), 1);
	game->map.start_index = i;
	return (0);
}

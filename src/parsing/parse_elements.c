/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:46:30 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 19:27:05 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int set_value(char **field, char *str)
{
    char *tmp;

    if (*field)
        return (1);
    tmp = ft_strdup(str);
    if (!tmp)
        return (1);
    *field = ft_strtrim(tmp, " \t\n");
    free(tmp);
    return (!*field);
}

static int	parse_element(t_game *game, char *str)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(str, "NO ", 3))
		ret = set_value(&game->textures.path_no, str + 3);
	else if (!ft_strncmp(str, "SO ", 3))
		ret = set_value(&game->textures.path_so, str + 3);
	else if (!ft_strncmp(str, "WE ", 3))
		ret = set_value(&game->textures.path_we, str + 3);
	else if (!ft_strncmp(str, "EA ", 3))
		ret = set_value(&game->textures.path_ea, str + 3);
	else if (!ft_strncmp(str, "F ", 2))
		ret = set_value(&game->textures.str_f, str + 2);
	else if (!ft_strncmp(str, "C ", 2))
		ret = set_value(&game->textures.str_c, str + 2);
	else
		ret = 1;
	return (free(str), ret);
}

int	parse_elements(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (game->map.lines[i])
	{
		line = ft_strtrim(game->map.lines[i], " \t\n");
		if (!line)
			return (free_parsing(game), 1);
		if (line[0] == '\0')
		{
			free(line);
			i++;
			continue ;
		}
		if (parse_element(game, line))
			break ;
		i++;
	}
	if (validate_values(game))
		return (1);
	game->map.start_index = i;
	return (0);
}

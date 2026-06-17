/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:46:46 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 12:53:43 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**read_lines(t_map *map, int fd)
{
	char	**lines;
	char	*line;
	int		i;

	lines = NULL;
	i = 0;
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines = ft_realloc(lines, sizeof(char *) * i, sizeof(char *) * (i + 2));
		lines[i] = line;
		lines[i + 1] = NULL;
		i++;
		line = ft_get_next_line(fd);
	}
	map->height = i;
	return (lines);
}

int	read_file(t_map *map, char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file", game), 1);
	map->lines = read_lines(map, fd);
	close(fd);
	if (!map->lines)
		return (error("failed to read file", game), 1);
	return (0);
}

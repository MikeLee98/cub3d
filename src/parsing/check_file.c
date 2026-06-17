/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:46:03 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:05:19 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_file(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file", game), 1);
	close(fd);
	return (0);
}

int	check_extension(char *path, t_game *game)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (error("invalid file extension", game), 1);
	return (0);
}

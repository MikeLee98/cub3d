/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:46:20 by mario             #+#    #+#             */
/*   Updated: 2026/06/17 13:04:40 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (!ptr)
		return (malloc(new_size));
	new = malloc(new_size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}

int	error(char *message, t_game *game)
{
	ft_printf("Error\n%s\n", message);
	free_parsing(game);
	return (1);
}

char	**copy_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = ft_calloc(map->height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
			return (free_split(copy), NULL);
		i++;
	}
	return (copy);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

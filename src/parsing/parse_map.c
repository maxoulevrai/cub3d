/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/09/01 00:17:38 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_map_lines(char **src, char **dst, int count)
{
	int	index;
	int	len;

	index = 0;
	while (index < count)
	{
		len = (int)ft_strlen(src[index]);
		dst[index] = ft_calloc((size_t)(len + 1), sizeof(char));
		if (dst[index] == NULL)
			return (1);
		ft_strlcpy(dst[index], src[index], (size_t)(len + 1));
		index++;
	}
	return (0);
}

int	parse_map(t_game *game, char **lines, int count)
{
	char	**grid;

	if (game == NULL || lines == NULL || count <= 0)
		return (1);
	game->map.height = count;
	game->map.width = 0;
	grid = (char **)ft_calloc((size_t)(count + 1), sizeof(char *));
	if (grid == NULL)
		return (ft_error("malloc failed"), 1);
	if (copy_map_lines(lines, grid, count) != 0)
		return (free_dtab(grid), ft_error("malloc failed"), 1);
	if (validate_map_shape(game, grid, count) != 0)
		return (free_dtab(grid), ft_error("Invalid map"), 1);
	if (map_is_closed(grid, count) == 0)
		return (free_dtab(grid), ft_error("Map is not closed"), 1);
	game->map.grid = grid;
	return (0);
}

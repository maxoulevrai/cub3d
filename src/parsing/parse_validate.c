/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:17:38 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static int	compute_width(char **grid, int count)
{
	int	index;
	int	width;
	int	len;

	width = 0;
	index = 0;
	while (index < count)
	{
		len = (int)ft_strlen(grid[index]);
		if (len > width)
			width = len;
		index++;
	}
	return (width);
}

static int	validate_row_chars(char *row)
{
	int	index;

	index = 0;
	while (row[index] != '\0')
	{
		if (is_map_char(row[index]) == 0)
			return (1);
		index++;
	}
	return (0);
}

static int	validate_all_chars(char **grid, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		if (validate_row_chars(grid[index]) != 0)
			return (1);
		index++;
	}
	return (0);
}

int	validate_map_shape(t_game *game, char **grid, int count)
{
	if (validate_all_chars(grid, count) != 0)
		return (1);
	game->map.width = compute_width(grid, count);
	if (locate_player(game, grid, count) != 0)
		return (1);
	return (0);
}

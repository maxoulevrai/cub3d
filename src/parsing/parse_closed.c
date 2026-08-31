/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 01:24:35 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_out_of_bounds(char **grid, int count, int x, int y)
{
	if (y < 0 || y >= count)
		return (1);
	if (x < 0 || (size_t)x >= ft_strlen(grid[y]))
		return (1);
	return (0);
}

static int	cell_is_closed(char **grid, int count, int x, int y)
{
	if (is_out_of_bounds(grid, count, x, y - 1))
		return (0);
	if (is_out_of_bounds(grid, count, x, y + 1))
		return (0);
	if (is_out_of_bounds(grid, count, x - 1, y))
		return (0);
	if (is_out_of_bounds(grid, count, x + 1, y))
		return (0);
	return (1);
}

static int	check_row(char **grid, int count, char *row, int y)
{
	int	x;

	x = 0;
	while (row[x] != '\0')
	{
		if (row[x] == '0' && cell_is_closed(grid, count, x, y) == 0)
			return (0);
		x++;
	}
	return (1);
}

int	map_is_closed(char **grid, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if (check_row(grid, height, grid[y], y) == 0)
			return (0);
		y++;
	}
	return (1);
}

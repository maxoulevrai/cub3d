/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:17:38 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_player_in_row(t_game *game, char *row, int y, int *found)
{
	int	index;

	index = 0;
	while (row[index] != '\0')
	{
		if (is_player_char(row[index]))
		{
			if (*found != 0)
				return (1);
			if (map_set_player(game, row[index], index, y) != 0)
				return (1);
			*found = 1;
			row[index] = '0';
		}
		index++;
	}
	return (0);
}

int	locate_player(t_game *game, char **grid, int count)
{
	int	index;
	int	found;

	found = 0;
	index = 0;
	while (index < count)
	{
		if (find_player_in_row(game, grid[index], index, &found) != 0)
			return (1);
		index++;
	}
	if (found == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 00:00:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_char_ok(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

static int	set_player_dir(t_game *game, char c, int x, int y)
{
	if (c == 'N')
		game->player.dir_x = 0.0, game->player.dir_y = -1.0, game->player.plane_x = 0.66, game->player.plane_y = 0.0;
	else if (c == 'S')
		game->player.dir_x = 0.0, game->player.dir_y = 1.0, game->player.plane_x = -0.66, game->player.plane_y = 0.0;
	else if (c == 'E')
		game->player.dir_x = 1.0, game->player.dir_y = 0.0, game->player.plane_x = 0.0, game->player.plane_y = 0.66;
	else if (c == 'W')
		game->player.dir_x = -1.0, game->player.dir_y = 0.0, game->player.plane_x = 0.0, game->player.plane_y = -0.66;
	else
		return (1);
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	return (0);
}

static int	validate_map_shape(t_game *game, char **grid, int count)
{
	int		players;
	int		y;
	int		x;
	int		len;

	players = 0;
	y = 0;
	while (y < count)
	{
		len = (int)ft_strlen(grid[y]);
		if (len > game->map.width)
			game->map.width = len;
		x = 0;
		while (x < len)
		{
			if (map_char_ok(grid[y][x]) == 0)
				return (1);
			if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'E' || grid[y][x] == 'W')
			{
				players++;
				if (players > 1 || set_player_dir(game, grid[y][x], x, y) != 0)
					return (1);
				grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (players != 1)
		return (1);
	return (0);
}

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
	game->map.grid = grid;
	return (0);
}

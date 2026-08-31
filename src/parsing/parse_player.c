/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:17:38 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_facing_north(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
}

static void	set_facing_south(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
}

static void	set_facing_east(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}

static void	set_facing_west(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
}

int	map_set_player(t_game *game, char direction, int x, int y)
{
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	if (direction == 'N')
		set_facing_north(game);
	else if (direction == 'S')
		set_facing_south(game);
	else if (direction == 'E')
		set_facing_east(game);
	else if (direction == 'W')
		set_facing_west(game);
	else
		return (1);
	return (0);
}

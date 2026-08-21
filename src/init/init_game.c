/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 15:24:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_defaults(t_game *game)
{
	game->player.x = 2.5;
	game->player.y = 2.5;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->move_speed = 0.08;
	game->rot_speed = 0.05;
	game->quit = 0;
}

static void	init_map_defaults(t_game *game)
{
	game->map.width = 0;
	game->map.height = 0;
	game->map.grid = NULL;
	game->map.floor.r = 0;
	game->map.floor.g = 0;
	game->map.floor.b = 0;
	game->map.ceiling.r = 0;
	game->map.ceiling.g = 0;
	game->map.ceiling.b = 0;
}

static void	init_texture_defaults(t_game *game)
{
	int	index;

	index = 0;
	while (index < TEX_COUNT)
	{
		game->texture[index].path = NULL;
		game->texture[index].img = NULL;
		game->texture[index].addr = NULL;
		game->texture[index].width = 0;
		game->texture[index].height = 0;
		game->texture[index].bpp = 0;
		game->texture[index].line_len = 0;
		game->texture[index].endian = 0;
		index++;
	}
}

int	init_game(t_game *game)
{
	int	index;

	if (game == NULL)
		return (1);
	index = 0;
	while (index < KEY_COUNT)
	{
		game->key[index] = 0;
		index++;
	}
	init_map_defaults(game);
	init_player_defaults(game);
	init_texture_defaults(game);
	return (0);
}

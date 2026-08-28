/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/28 14:19:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	blocked(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map.height || map_x < 0)
		return (1);
	if (game->map.grid[map_y] == NULL
		|| map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	return (game->map.grid[map_y][map_x] != '0');
}

static void	try_move(t_game *game, double x, double y)
{
	if (!blocked(game, x, game->player.y)
		&& !blocked(game, x, y) && !blocked(game, game->player.x, y))
		game->player.x = x;
	if (!blocked(game, game->player.x, y))
		game->player.y = y;
}

static void	move_direction(t_game *game, double direction)
{
	double	x;
	double	y;

	x = game->player.x + game->player.dir_x * game->move_speed * direction;
	y = game->player.y + game->player.dir_y * game->move_speed * direction;
	try_move(game, x, y);
}

static void	strafe(t_game *game, double direction)
{
	double	x;
	double	y;

	x = game->player.x + game->player.dir_y * game->move_speed * direction;
	y = game->player.y - game->player.dir_x * game->move_speed * direction;
	try_move(game, x, y);
}

void	move_player(t_game *game)
{
	if (game->key['w'])
		move_direction(game, 1.0);
	if (game->key['s'])
		move_direction(game, -1.0);
	if (game->key['a'])
		strafe(game, 1.0);
	if (game->key['d'])
		strafe(game, -1.0);
	if (game->key[65361])
		rotate_player(game, -game->rot_speed);
	if (game->key[65363])
		rotate_player(game, game->rot_speed);
}

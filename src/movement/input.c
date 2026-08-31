/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/28 14:18:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (game == NULL)
		return (1);
	if (keycode == KEY_ESC)
		return (close_game(game));
	if (keycode >= 0 && keycode < KEY_COUNT)
		game->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (game == NULL)
		return (1);
	if (keycode >= 0 && keycode < KEY_COUNT)
		game->key[keycode] = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	if (game == NULL || game->quit != 0)
		return (1);
	move_player(game);
	return (render_frame(game));
}

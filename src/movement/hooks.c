/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/09/01 00:00:19 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_key_press(int keycode, void *param)
{
	return (key_press(keycode, (t_game *)param));
}

int	hook_key_release(int keycode, void *param)
{
	return (key_release(keycode, (t_game *)param));
}

int	hook_game_loop(void *param)
{
	return (game_loop((t_game *)param));
}

void	set_mlx_hooks(t_game *game)
{
	union u_callback	callback;

	callback.close_callback = close_game;
	mlx_hook(game->mlx.win_ptr, 17, 0, callback.mlx_callback, game);
	callback.key_callback = hook_key_press;
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, callback.mlx_callback, game);
	callback.key_callback = hook_key_release;
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, callback.mlx_callback, game);
	callback.loop_callback = hook_game_loop;
	mlx_loop_hook(game->mlx.mlx_ptr, callback.mlx_callback, game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/09/01 01:03:29 by yzidani          ###   ########.fr       */
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
	game->move_speed = 0.05;
	game->rot_speed = 0.02;
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

int	init_game(t_game *game)
{
	int	index;

	if (game == NULL)
		return (1);
	game->mlx.mlx_ptr = NULL;
	game->mlx.win_ptr = NULL;
	game->mlx.img_ptr = NULL;
	game->mlx.img_addr = NULL;
	game->mlx.bpp = 0;
	game->mlx.line_len = 0;
	game->mlx.endian = 0;
	game->config_mask = 0;
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

int	close_game(t_game *game)
{
	if (game == NULL)
		return (1);
	game->quit = 1;
	mlx_loop_end(game->mlx.mlx_ptr);
	return (0);
}

int	init_mlx(t_game *game)
{
	if (game == NULL)
		return (1);
	game->mlx.mlx_ptr = mlx_init();
	if (game->mlx.mlx_ptr == NULL)
		return (ft_error("MiniLibX initialization failed"), 1);
	if (load_textures(game) != 0)
		return (1);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->mlx.win_ptr == NULL)
		return (ft_error("Window creation failed"), 1);
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	if (game->mlx.img_ptr == NULL)
		return (ft_error("Image creation failed"), 1);
	game->mlx.img_addr = mlx_get_data_addr(game->mlx.img_ptr,
			&game->mlx.bpp, &game->mlx.line_len, &game->mlx.endian);
	if (game->mlx.img_addr == NULL)
		return (ft_error("Image buffer creation failed"), 1);
	set_mlx_hooks(game);
	return (0);
}

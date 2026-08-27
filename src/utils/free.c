/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/26 16:47:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_game *game)
{
	int	index;

	index = 0;
	while (index < TEX_COUNT)
	{
		if (game->texture[index].path != NULL)
		{
			free(game->texture[index].path);
			game->texture[index].path = NULL;
		}
		if (game->texture[index].img != NULL)
		{
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[index].img);
			game->texture[index].img = NULL;
		}
		index++;
	}
}

static void	free_mlx(t_game *game)
{
	if (game->mlx.img_ptr != NULL)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
		game->mlx.img_ptr = NULL;
	}
	if (game->mlx.win_ptr != NULL)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		game->mlx.win_ptr = NULL;
	}
	free_textures(game);
	if (game->mlx.mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
}

void	free_game(t_game *game)
{
	int	index;

	if (game == NULL)
		return ;
	free_mlx(game);
	index = 0;
	while (game->map.grid != NULL && game->map.grid[index] != NULL)
	{
		free(game->map.grid[index]);
		index++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

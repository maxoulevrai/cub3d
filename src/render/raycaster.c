/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 15:24:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	color_value(t_color color)
{
	return ((unsigned int)(color.r << 16)
		| (unsigned int)(color.g << 8) | (unsigned int)color.b);
}

static void	put_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = game->mlx.img_addr + y * game->mlx.line_len
		+ x * (game->mlx.bpp / 8);
	*(unsigned int *)pixel = color;
}

static void	draw_background(t_game *game)
{
	int		x;
	int		y;
	unsigned int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		if (y < WIN_HEIGHT / 2)
			color = color_value(game->map.ceiling);
		else
			color = color_value(game->map.floor);
		while (x < WIN_WIDTH)
			put_pixel(game, x++, y, color);
		y++;
	}
}

int	render_frame(t_game *game)
{
	if (game == NULL || game->mlx.img_ptr == NULL || game->mlx.win_ptr == NULL)
		return (1);
	draw_background(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}

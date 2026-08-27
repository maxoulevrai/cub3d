/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/26 16:56:41 by root             ###   ########.fr       */
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

void	draw_background(t_game *game)
{
	int			x;
	int			y;
	int			color;

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

static unsigned int	texture_color(t_game *game, t_ray *ray, int y,
	int line_height)
{
	t_texture	*texture;
	char		*pixel;

	texture = &game->texture[ray->tex_id];
	ray->tex_y = (y - (WIN_HEIGHT - line_height) / 2)
		* texture->height / line_height;
	pixel = texture->addr + ray->tex_y * texture->line_len
		+ ray->tex_x * (texture->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		color = texture_color(game, ray, y, line_height);
		put_pixel(game, x, y++, color);
	}
}

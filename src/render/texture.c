/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/26 16:58:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, int index)
{
	t_texture	*texture;

	texture = &game->texture[index];
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, texture->path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (texture->addr == NULL)
		return (1);
	return (0);
}

int	load_textures(t_game *game)
{
	int	index;

	index = 0;
	while (index < TEX_COUNT)
	{
		if (game->texture[index].path == NULL
			|| load_texture(game, index) != 0)
			return (ft_error("Texture loading failed"), 1);
		index++;
	}
	return (0);
}

void	set_texture_coords(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
		if (ray->dir_x > 0.0)
			ray->tex_id = 2;
		else
			ray->tex_id = 3;
	}
	else
	{
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
		if (ray->dir_y > 0.0)
			ray->tex_id = 0;
		else
			ray->tex_id = 1;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x
			* game->texture[ray->tex_id].width);
	if ((ray->side == 0 && ray->dir_x > 0.0)
		|| (ray->side == 1 && ray->dir_y < 0.0))
		ray->tex_x = game->texture[ray->tex_id].width - ray->tex_x - 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/26 16:58:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->delta_dist_x = 1e30;
	ray->delta_dist_y = 1e30;
	if (ray->dir_x != 0.0)
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y != 0.0)
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	set_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->map_y >= 0 && ray->map_y < game->map.height
		&& ray->map_x >= 0 && ray->map_x < game->map.width
		&& game->map.grid[ray->map_y][ray->map_x] != '1'
		&& game->map.grid[ray->map_y][ray->map_x] != ' ')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

static void	set_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->map_x - game->player.x;
		ray->perp_wall_dist += (1 - ray->step_x) / 2.0;
		ray->perp_wall_dist /= ray->dir_x;
	}
	else
	{
		ray->perp_wall_dist = ray->map_y - game->player.y;
		ray->perp_wall_dist += (1 - ray->step_y) / 2.0;
		ray->perp_wall_dist /= ray->dir_y;
	}
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	set_texture_coords(game, ray);
}

int	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	if (game == NULL || game->mlx.img_ptr == NULL || game->mlx.win_ptr == NULL)
		return (1);
	draw_background(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		set_ray_steps(game, &ray);
		perform_dda(game, &ray);
		set_wall_distance(game, &ray);
		draw_wall(game, &ray, x++);
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}

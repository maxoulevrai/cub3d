/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/28 14:18:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_SIZE 64
# define TEX_COUNT 4
# define KEY_COUNT 256
# define ERR_MSG "Error\n"
# define KEY_W 25
# define KEY_A 38
# define KEY_S 39
# define KEY_D 40
# define KEY_LEFT 113
# define KEY_RIGHT 114
# define KEY_ESC 9

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	t_color	floor;
	t_color	ceiling;
} t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
} t_texture;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		tex_id;
} t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_texture	texture[TEX_COUNT];
	int		key[KEY_COUNT];
	int			config_mask;
	double		move_speed;
	double		rot_speed;
	int		quit;
} t_game;

int		init_game(t_game *game);
int		init_mlx(t_game *game);
int		parse_file(t_game *game, char *path);
int		parse_map(t_game *game, char **lines, int count);
void	draw_background(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);
int		load_textures(t_game *game);
void	set_texture_coords(t_game *game, t_ray *ray);
int		render_frame(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		game_loop(t_game *game);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double angle);
int		close_game(t_game *game);
void	free_game(t_game *game);
void	ft_error(const char *message);

#endif

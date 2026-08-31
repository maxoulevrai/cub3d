/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/09/01 01:01:31 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_SIZE 64
# define TEX_COUNT 4
# define KEY_COUNT 65536
# define ERR_MSG "Error\n"
# define KEY_W XK_w
# define KEY_A XK_a
# define KEY_S XK_s
# define KEY_D XK_d
# define KEY_LEFT XK_Left
# define KEY_RIGHT XK_Right
# define KEY_ESC XK_Escape

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	t_color	floor;
	t_color	ceiling;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

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
}	t_texture;

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
}	t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_texture	texture[TEX_COUNT];
	int			key[KEY_COUNT];
	int			config_mask;
	double		move_speed;
	double		rot_speed;
	int			quit;
}	t_game;

union u_callback
{
	int	(*mlx_callback)(void);
	int	(*close_callback)(t_game *game);
	int	(*key_callback)(int keycode, void *param);
	int	(*loop_callback)(void *param);
};

int		init_game(t_game *game);
int		init_mlx(t_game *game);
int		parse_file(t_game *game, char *path);
int		parse_map(t_game *game, char **lines, int count);
int		read_map_file(char *path, char ***lines_ptr, int *count_ptr);
int		parse_config_line(t_game *game, char *line);
int		parse_color_line(t_game *game, char *line, int is_floor);
int		validate_map_shape(t_game *game, char **grid, int count);
int		locate_player(t_game *game, char **grid, int count);
int		map_is_closed(char **grid, int height);
int		map_set_player(t_game *game, char direction, int x, int y);
void	init_texture_defaults(t_game *game);
void	draw_background(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);
int		load_textures(t_game *game);
void	set_texture_coords(t_game *game, t_ray *ray);
int		render_frame(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		game_loop(t_game *game);
int		hook_key_press(int keycode, void *param);
int		hook_key_release(int keycode, void *param);
int		hook_game_loop(void *param);
void	set_mlx_hooks(t_game *game);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double angle);
int		close_game(t_game *game);
void	free_game(t_game *game);
void	ft_error(const char *message);

#endif

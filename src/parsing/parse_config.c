/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:00:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	texture_index(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 3) == 0)
		return (0);
	if (ft_strncmp(identifier, "SO", 3) == 0)
		return (1);
	if (ft_strncmp(identifier, "WE", 3) == 0)
		return (2);
	if (ft_strncmp(identifier, "EA", 3) == 0)
		return (3);
	return (-1);
}

static int	parse_texture(t_game *game, char *line)
{
	char	**parts;
	int		index;

	parts = ft_split(line, ' ');
	if (parts == NULL || get_dtab_len(parts) != 2)
		return (free_dtab(parts), 1);
	index = texture_index(parts[0]);
	if (index < 0 || (game->config_mask & (1 << index)) != 0)
		return (free_dtab(parts), 1);
	game->texture[index].path = ft_strdup(parts[1]);
	if (game->texture[index].path == NULL)
		return (free_dtab(parts), 1);
	game->config_mask |= (1 << index);
	free_dtab(parts);
	return (0);
}

static int	is_texture(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

int	parse_config_line(t_game *game, char *line)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (trimmed == NULL || trimmed[0] == '\0')
		return (free(trimmed), 1);
	if (is_texture(trimmed))
		ret = parse_texture(game, trimmed);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		ret = parse_color_line(game, trimmed, 1);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		ret = parse_color_line(game, trimmed, 0);
	else
		ret = 1;
	free(trimmed);
	return (ret);
}

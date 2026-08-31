/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:00:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_component(char *component, int *value)
{
	int	index;

	if (component[0] == '\0')
		return (1);
	*value = 0;
	index = 0;
	while (component[index] >= '0' && component[index] <= '9')
	{
		if (*value > 25 || (*value == 25 && component[index] > '5'))
			return (1);
		*value = *value * 10 + component[index] - '0';
		index++;
	}
	if (component[index] != '\0')
		return (1);
	return (0);
}

static int	parse_components(char **rgb, int *values)
{
	int	index;

	index = 0;
	while (index < 3)
	{
		if (parse_component(rgb[index], &values[index]) != 0)
			return (1);
		index++;
	}
	return (0);
}

static void	set_color(t_game *game, int *values, int is_floor)
{
	if (is_floor)
	{
		game->map.floor.r = values[0];
		game->map.floor.g = values[1];
		game->map.floor.b = values[2];
		game->config_mask |= 16;
	}
	else
	{
		game->map.ceiling.r = values[0];
		game->map.ceiling.g = values[1];
		game->map.ceiling.b = values[2];
		game->config_mask |= 32;
	}
}

int	parse_color_line(t_game *game, char *line, int is_floor)
{
	char	**parts;
	char	**rgb;
	int		values[3];
	int		ret;

	parts = ft_split(line, ' ');
	if (parts == NULL || get_dtab_len(parts) != 2)
		return (free_dtab(parts), 1);
	rgb = ft_split(parts[1], ',');
	if (rgb == NULL || get_dtab_len(rgb) != 3)
		return (free_dtab(parts), free_dtab(rgb), 1);
	ret = parse_components(rgb, values);
	if (ret == 0)
		set_color(game, values, is_floor);
	free_dtab(parts);
	free_dtab(rgb);
	return (ret);
}

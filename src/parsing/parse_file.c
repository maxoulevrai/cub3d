/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/09/01 00:09:20 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

static int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

static int	parse_lines(t_game *game, char **lines, int count)
{
	int	index;
	int	ret;

	index = 0;
	while (index < count)
	{
		if (line_is_empty(lines[index]))
			index++;
		else if (is_map_line(lines[index]) == 0)
		{
			ret = parse_config_line(game, lines[index]);
			if (ret != 0)
				return (ft_error("Invalid .cub line"), 1);
			index++;
		}
		else
			return (parse_map(game, &lines[index], count - index));
	}
	ft_error("Map not found");
	return (1);
}

int	parse_file(t_game *game, char *path)
{
	char	**lines;
	int		count;
	int		ret;

	if (game == NULL || path == NULL)
		return (1);
	ret = read_map_file(path, &lines, &count);
	if (ret != 0)
		return (ret);
	ret = parse_lines(game, lines, count);
	free_dtab(lines);
	if (ret != 0)
		return (ret);
	if (game->config_mask != 63)
		return (ft_error("Missing map configuration"), 1);
	return (0);
}

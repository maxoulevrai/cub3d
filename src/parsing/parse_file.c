/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 15:30:08 by root             ###   ########.fr       */
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

static int	total_read_lines(int fd, char ***lines_ptr)
{
	char	**lines;
	char	**new_lines;
	char	*line;
	int		count;
	int		index;

	count = 16;
	lines = (char **)ft_calloc((size_t)(count + 1), sizeof(char *));
	if (lines == NULL)
		return (-1);
	index = 0;
	line = get_next_line(fd, "\n");
	while (line != NULL)
	{
		if (index >= count)
		{
			count *= 2;
			new_lines = ft_calloc((size_t)(count + 1), sizeof(char *));
			if (new_lines == NULL)
				return (free(line), free_dtab(lines), -1);
			ft_memcpy(new_lines, lines, sizeof(char *) * (size_t)index);
			free(lines);
			lines = new_lines;
		}
		lines[index++] = line;
		line = get_next_line(fd, "\n");
	}
	*lines_ptr = lines;
	return (index);
}

static int	parse_texture_value(t_game *game, char *line)
{
	char	**parts;
	char	*path;
	int		ret;

	parts = ft_split(line, ' ');
	if (parts == NULL || get_dtab_len(parts) != 2)
		ret = 1;
	else if (ft_strncmp(parts[0], "NO", 3) == 0)
		path = ft_strdup(parts[1]), game->texture[0].path = path, game->config_mask |= 1, ret = path == NULL;
	else if (ft_strncmp(parts[0], "SO", 3) == 0)
		path = ft_strdup(parts[1]), game->texture[1].path = path, game->config_mask |= 2, ret = path == NULL;
	else if (ft_strncmp(parts[0], "WE", 3) == 0)
		path = ft_strdup(parts[1]), game->texture[2].path = path, game->config_mask |= 4, ret = path == NULL;
	else if (ft_strncmp(parts[0], "EA", 3) == 0)
		path = ft_strdup(parts[1]), game->texture[3].path = path, game->config_mask |= 8, ret = path == NULL;
	else
		ret = 1;
	free_dtab(parts);
	return (ret);
}

static int	parse_color_parts(t_game *game, char *line, int is_floor)
{
	char	**parts;
	char	**rgb;
	int		value[3];
	int		index;
	int		digit;

	parts = ft_split(line, ' ');
	if (parts == NULL || get_dtab_len(parts) != 2)
		return (1);
	rgb = ft_split(parts[1], ',');
	if (rgb == NULL || get_dtab_len(rgb) != 3)
		return (free_dtab(parts), 1);
	index = 0;
	while (index < 3)
	{
		value[index] = 0;
		if (rgb[index][0] == '\0')
			return (free_dtab(parts), free_dtab(rgb), 1);
		digit = 0;
		while (rgb[index][digit] >= '0' && rgb[index][digit] <= '9')
		{
			if (value[index] > 25
				|| (value[index] == 25 && rgb[index][digit] > '5'))
				return (free_dtab(parts), free_dtab(rgb), 1);
			value[index] = value[index] * 10
				+ (rgb[index][digit] - '0');
			digit++;
		}
		if (rgb[index][digit] != '\0')
			return (free_dtab(parts), free_dtab(rgb), 1);
		index++;
	}
	if (is_floor)
	{
		game->map.floor.r = value[0];
		game->map.floor.g = value[1];
		game->map.floor.b = value[2];
		game->config_mask |= 16;
	}
	else
	{
		game->map.ceiling.r = value[0];
		game->map.ceiling.g = value[1];
		game->map.ceiling.b = value[2];
		game->config_mask |= 32;
	}
	free_dtab(parts);
	free_dtab(rgb);
	return (0);
}

static int	parse_line_config(t_game *game, char *line)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (trimmed == NULL)
		return (1);
	if (trimmed[0] == '\0')
		return (free(trimmed), 1);
	ret = 1;
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		&& (game->config_mask & 1) == 0)
		ret = parse_texture_value(game, trimmed);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0
		&& (game->config_mask & 2) == 0)
		ret = parse_texture_value(game, trimmed);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0
		&& (game->config_mask & 4) == 0)
		ret = parse_texture_value(game, trimmed);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0
		&& (game->config_mask & 8) == 0)
		ret = parse_texture_value(game, trimmed);
	else if (ft_strncmp(trimmed, "F ", 2) == 0
		&& (game->config_mask & 16) == 0)
		ret = parse_color_parts(game, trimmed, 1);
	else if (ft_strncmp(trimmed, "C ", 2) == 0
		&& (game->config_mask & 32) == 0)
		ret = parse_color_parts(game, trimmed, 0);
	free(trimmed);
	return (ret);
}

static int	read_map_file(char *path, char ***lines_ptr, int *count_ptr)
{
	char	**lines;
	int		fd;
	int		count;
	int		index;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Invalid map file"), 1);
	count = total_read_lines(fd, &lines);
	close(fd);
	if (count < 0)
		return (ft_error("malloc failed"), 1);
	index = 0;
	while (index < count)
	{
		line = ft_strtrim(lines[index], "\r\n");
		if (line == NULL)
			return (free_dtab(lines), 1);
		free(lines[index]);
		lines[index] = line;
		index++;
	}
	*lines_ptr = lines;
	*count_ptr = count;
	return (0);
}

int	parse_file(t_game *game, char *path)
{
	char	**lines;
	int		count;
	int		index;
	int		ret;

	if (game == NULL || path == NULL)
		return (1);
	ret = read_map_file(path, &lines, &count);
	if (ret != 0)
		return (ret);
	index = 0;
	while (index < count)
	{
		if (line_is_empty(lines[index]))
			index++;
		else if (is_map_line(lines[index]) == 0)
		{
			ret = parse_line_config(game, lines[index]);
			if (ret != 0)
				return (free_dtab(lines), ft_error("Invalid .cub line"), 1);
			index++;
		}
		else
		{
			ret = parse_map(game, &lines[index], count - index);
			free_dtab(lines);
			if (ret != 0)
				return (ret);
			if (game->config_mask != 63)
					return (ft_error("Missing map configuration"), 1);
				return (0);
		}
	}
	free_dtab(lines);
	ft_error("Map not found");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:00:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	grow_lines(char ***lines_ptr, int *capacity, int index)
{
	char	**new_lines;

	*capacity *= 2;
	new_lines = ft_calloc((size_t)(*capacity + 1), sizeof(char *));
	if (new_lines == NULL)
		return (1);
	ft_memcpy(new_lines, *lines_ptr, sizeof(char *) * (size_t)index);
	free(*lines_ptr);
	*lines_ptr = new_lines;
	return (0);
}

static int	read_lines(int fd, char ***lines_ptr)
{
	char	**lines;
	char	*line;
	int		capacity;
	int		index;

	capacity = 16;
	lines = ft_calloc((size_t)(capacity + 1), sizeof(char *));
	if (lines == NULL)
		return (-1);
	index = 0;
	line = get_next_line(fd, "\n");
	while (line != NULL)
	{
		if (index >= capacity && grow_lines(&lines, &capacity, index) != 0)
			return (free(line), free_dtab(lines), -1);
		lines[index] = line;
		index++;
		line = get_next_line(fd, "\n");
	}
	*lines_ptr = lines;
	return (index);
}

static int	trim_lines(char **lines, int count)
{
	char	*line;
	int		index;

	index = 0;
	while (index < count)
	{
		line = ft_strtrim(lines[index], "\r\n");
		if (line == NULL)
			return (1);
		free(lines[index]);
		lines[index] = line;
		index++;
	}
	return (0);
}

int	read_map_file(char *path, char ***lines_ptr, int *count_ptr)
{
	char	**lines;
	int		fd;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Invalid map file"), 1);
	count = read_lines(fd, &lines);
	close(fd);
	if (count < 0)
		return (ft_error("malloc failed"), 1);
	if (trim_lines(lines, count) != 0)
		return (free_dtab(lines), 1);
	*lines_ptr = lines;
	*count_ptr = count;
	return (0);
}

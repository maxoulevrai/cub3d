/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 15:24:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		ret;

	if (argc != 2)
	{
		ft_error("Usage: ./cub3D <map.cub>");
		return (1);
	}
	ret = init_game(&game);
	if (ret != 0)
		return (ret);
	ret = parse_file(&game, argv[1]);
	if (ret != 0)
	{
		free_game(&game);
		return (ret);
	}
	ret = render_frame(&game);
	free_game(&game);
	return (ret);
}

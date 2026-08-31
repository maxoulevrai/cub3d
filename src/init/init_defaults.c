/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_defaults.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 00:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/09/01 00:00:19 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_defaults(t_game *game)
{
	int	index;

	index = 0;
	while (index < TEX_COUNT)
	{
		game->texture[index].path = NULL;
		game->texture[index].img = NULL;
		game->texture[index].addr = NULL;
		game->texture[index].width = 0;
		game->texture[index].height = 0;
		game->texture[index].bpp = 0;
		game->texture[index].line_len = 0;
		game->texture[index].endian = 0;
		index++;
	}
}

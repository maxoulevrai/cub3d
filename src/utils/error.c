/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/08/15 15:24:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(const char *message)
{
	if (message == NULL)
		write(2, ERR_MSG, ft_strlen(ERR_MSG));
	else
	{
		write(2, ERR_MSG, ft_strlen(ERR_MSG));
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
}

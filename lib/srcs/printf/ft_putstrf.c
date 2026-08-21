/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 04:02:59 by maleca            #+#    #+#             */
/*   Updated: 2026/08/15 15:27:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_putstrf(char *str, size_t *count)
{
	int	i;

	if (!str)
	{
		ft_putstrf("(null)", count);
		return ;
	}
	i = 0;
	while (str[i])
	{
		(*count)++;
		i++;
	}
	write(1, str, i);
}

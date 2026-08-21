/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddyf_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:43 by maleca            #+#    #+#             */
/*   Updated: 2026/08/15 15:27:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fprintf.h"

void	ft_putaddyf_fd(unsigned long long adresse, size_t *count, int fd)
{
	if (!adresse)
	{
		ft_putstrf_fd("(nil)", count, fd);
		return ;
	}
	ft_putstrf_fd("0x", count, fd);
	ft_putnbr_basef_fd(adresse, 'x', count, fd);
}

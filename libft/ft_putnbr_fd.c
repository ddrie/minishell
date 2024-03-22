/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:54:04 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 14:54:10 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lon;

	lon = n;
	if (lon < 0)
	{
		ft_putchar_fd('-', fd);
		lon = lon * -1;
	}
	if (lon >= 10)
	{
		ft_putnbr_fd(lon / 10, fd);
	}
	ft_putchar_fd((lon % 10) + '0', fd);
}

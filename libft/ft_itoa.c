/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:50:52 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 14:50:54 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_fill_string(long lon, char *str, int len, int is_negative)
{
	if (lon == 0)
	{
		str[len - 1] = '0';
		return ;
	}
	while (lon != 0)
	{
		str[len - 1] = (lon % 10) + '0';
		lon /= 10;
		len--;
	}
	if (is_negative)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	long	lon;
	int		len;
	int		is_negative;
	char	*str;

	lon = n;
	len = ft_int_count(n);
	is_negative = 0;
	if (lon < 0)
	{
		lon = -lon;
		len++;
		is_negative = 1;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_fill_string(lon, str, len, is_negative);
	return (str);
}

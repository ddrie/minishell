/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:59:50 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 14:59:52 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int			i;
	char		*strt;
	int			safe;

	if (ch > 256)
		safe = ch - 256;
	else
		safe = ch;
	strt = (char *)str;
	i = ft_strlen(strt);
	while (i >= 0)
	{
		if (strt[i] == safe)
			return ((char *)strt + i);
		i--;
	}
	return (0);
}

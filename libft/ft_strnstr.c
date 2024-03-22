/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:59:25 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/08 15:04:55 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	i = 0;
	while (i < len)
	{
		if (!*big || (little_len > len - i))
			return (0);
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		i++;
		big++;
	}
	return (0);
}

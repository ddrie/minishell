/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:55:16 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 14:55:40 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			terminator_index;
	unsigned char	c_char;

	c_char = c;
	if (c == 0)
	{
		terminator_index = ft_strlen(s);
		return ((char *)s + terminator_index);
	}
	else
	{
		while (*s)
		{
			if (c_char == *s)
				return ((char *)s);
			s++;
		}
		return (0);
	}
}

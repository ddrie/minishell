/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:00:26 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 15:00:28 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*buf;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		buf = malloc(sizeof(char));
		if (!buf)
			return (NULL);
		*buf = '\0';
	}
	else
	{
		if ((ft_strlen(s) - start < len))
			len = ft_strlen(s) - start;
		buf = malloc(sizeof(char) * len +1);
		if (!buf)
			return (NULL);
		ft_strlcpy(buf, (char *)(s + start), len + 1);
	}
	return (buf);
}

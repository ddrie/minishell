/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:55:58 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 14:56:01 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*t;

	len = ft_strlen(s);
	t = malloc(len + 1);
	if (!t)
		return (NULL);
	ft_memcpy(t, s, len);
	t[len] = '\0';
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:00:07 by dmavliut          #+#    #+#             */
/*   Updated: 2023/07/06 15:00:09 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*out;

	if (!s1 || !set)
		return (0);
	if (set[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	if (end)
	{
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
	}
	if (start > end)
		end = start;
	out = malloc(end - start + 1);
	if (!out)
		return (0);
	ft_memcpy(out, s1 + start, end - start);
	out[end - start] = 0;
	return (out);
}

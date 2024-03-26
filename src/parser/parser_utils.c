/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:52:28 by cgray             #+#    #+#             */
/*   Updated: 2024/03/25 17:14:56 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_token *cmds)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_args(t_token *cmds)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == T_IDENTIFIER)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_token	skip_to_cmd(t_token *cmds)
{
	t_token	*tmp;

	tmp = cmds;
	while (tmp && tmp->type != T_PIPE)
		tmp = tmp->next;
	return (*tmp);
}

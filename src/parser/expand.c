/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:48:23 by cgray             #+#    #+#             */
/*   Updated: 2024/03/26 16:11:41 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* iterates through list of tokens, replacing the value string
with the envp variable if found.

Maybe should change the type as well? */
void	expand_variables(t_token **tokens, t_envp *envp_list)
{
	char	*variable;

	while (*tokens)
	{
		if ((*tokens)->type == T_DOLLAR)
		{
			variable = find_key(envp_list, (*tokens)->value + 1);
			if (variable)
			{
				free((*tokens)->value);
				(*tokens)->value = ft_strdup(variable);
			}
		}
		tokens = &(*tokens)->next;
	}
}

/* expected to call during parsing, after handling quotes/esc chars */

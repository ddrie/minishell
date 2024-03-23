/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_add_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:05:20 by dmavliut          #+#    #+#             */
/*   Updated: 2024/03/23 16:05:22 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("Failed to allocate memory for token");
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	if (value != NULL)
	{
		new_token->value = ft_strdup(value);
	}
	else
	{
		new_token->value = NULL;
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (!*token_list)
	{
		*token_list = new_token;
	}
	else
	{
		temp = *token_list;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_token;
	}
}

void	free_tokens(t_token **token_list)
{
	t_token	*temp;

	while (*token_list)
	{
		temp = (*token_list)->next;
		free((*token_list)->value);
		free(*token_list);
		*token_list = temp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianamavlutova <dianamavlutova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:06:05 by dmavliut          #+#    #+#             */
/*   Updated: 2024/03/25 10:41:11 by dianamavlut      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

void	handle_quotes(const char **input, t_token **tokens, char quoteType)
{
	const char	*start;
	char		*val;

	start = ++(*input);
	while (**input && **input != quoteType)
	{
		(*input)++;
	}
	if (**input == quoteType)
	{
		val = strndup(start, *input - start);
		add_token(tokens, create_token(T_QUOTE, val));
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

void	handle_operator(const char **input, t_token **tokens, char op)
{
	const char		*op_str;
	t_token_type	type;

	if (op == '<')
	{
		if (*(*input + 1) == '<')
		{
			op_str = "<<";
			type = T_LESSLESS;
			(*input)++;
		}
		else
		{
			op_str = "<";
			type = T_LESS;
		}
	}
	else if (op == '>')
	{
		if (*(*input + 1) == '>')
		{
			op_str = ">>";
			type = T_GREATGREAT;
			(*input)++;
		}
		else
		{
			op_str = ">";
			type = T_GREAT;
		}
	}
	else if (op == '|')
	{
		op_str = "|";
		type = T_PIPE;
	}
	add_token(tokens, create_token(type, op_str));
}

void	handle_env_var(const char **input, t_token **tokens)
{
	const char	*start;
	char		*val;

	start = *input;
	while (ft_isalnum(*(*input + 1)) || *(*input + 1) == '_')
	{
		(*input)++;
	}
	if (*input > start)
	{
		val = ft_strndup(start, *input - start + 1);
		add_token(tokens, create_token(T_DOLLAR, val));
	}
	else
	{
		add_token(tokens, create_token(T_UNKNOWN, "$"));
	}
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = 0;
	while (s1[len] && len < n)
		len++;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:05:37 by dmavliut          #+#    #+#             */
/*   Updated: 2024/03/23 16:05:38 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

void	add_identifier_token(const char **start, const char *end,
		t_token **tokens)
{
	char	*val;

	if (*start < end)
	{
		val = ft_strndup(*start, end - *start);
		add_token(tokens, create_token(T_IDENTIFIER, val));
	}
}

void	lexer_recursive(const char *input, const char *start, t_token **tokens)
{
	if (!*input)
	{
		add_identifier_token(&start, input, tokens);
		return ;
	}
	if (*input == '<' || *input == '>')
	{
		add_identifier_token(&start, input, tokens);
		handle_operator(&input, tokens, *input);
	}
	else if (*input == '|')
	{
		add_identifier_token(&start, input, tokens);
		handle_operator(&input, tokens, *input);
	}
	else if (ft_isspace(*input))
	{
		add_identifier_token(&start, input, tokens);
		start = input + 1;
	}
	else if (*input == '$')
	{
		add_identifier_token(&start, input, tokens);
		handle_env_var(&input, tokens);
		start = input + 1;
	}
	lexer_recursive(input + 1, start, tokens);
}

void	lexer(const char *input, t_token **tokens)
{
	lexer_recursive(input, input, tokens);
}

/*
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}
int	main(void)
{
	const char	*input;
	t_token		*tokens;

	input = "cat < input.txt > output.txt | grep 'something'";
	tokens = NULL;
	lexer(input, &tokens);
	print_tokens(tokens);
	free_tokens(&tokens);
	return (0);
}
*/

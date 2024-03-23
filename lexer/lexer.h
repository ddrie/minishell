/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmavliut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:05:51 by dmavliut          #+#    #+#             */
/*   Updated: 2024/03/23 16:05:53 by dmavliut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum token_type
{
	T_UNKNOWN,
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_LESSLESS,
	T_GREATGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
	T_QUOTE,
	T_DOLLAR,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// Function Prototypes
t_token				*create_token(t_token_type type, const char *value);
void				add_token(t_token **token_list, t_token *new_token);
void				free_tokens(t_token **token_list);
void				lexer(const char *input, t_token **tokens);
void				print_tokens(t_token *tokens);
bool				ft_isspace(char c);
void				add_identifier_token(const char **start, const char *end,
						t_token **tokens);
void				handle_quotes(const char **input, t_token **tokens,
						char quoteType);
void				handle_operator(const char **input, t_token **tokens,
						char op);
void				handle_env_var(const char **input, t_token **tokens);
char				*ft_strndup(const char *s1, size_t n);

#endif

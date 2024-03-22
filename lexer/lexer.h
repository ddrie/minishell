#ifndef TOKENIZING_H
# define TOKENIZING_H

# define PROMPT "minishell$ "

typedef enum e_token_type
{
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
}	t_token_type;

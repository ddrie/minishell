#include "lexer.h" 
#include "../libft/libft.h"

bool ft_isspace(char c) 
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

void handle_quotes(const char **input, t_token **tokens, char quoteType) 
{
    const char *start = ++(*input);
    while (**input && **input != quoteType) 
    {
        (*input)++;
    }
    if (**input == quoteType) 
    {
        char *val = strndup(start, *input - start);
        add_token(tokens, create_token(T_QUOTE, val));
    } 
    else 
    {
        printf("Error! Unmatched quotes\n");
        exit(EXIT_FAILURE);
    }
}


void handle_operator(const char **input, t_token **tokens, char op) 
{
    if (op == '<' || op == '>') 
    {
        const char *op_str = (op == '<') ? "<" : ">";
        t_token_type type = (op == '<') ? T_LESS : T_GREAT;
        if (*(*input + 1) == op) 
        {
            op_str = (op == '<') ? "<<" : ">>";
            type = (op == '<') ? T_LESSLESS : T_GREATGREAT;
            (*input)++;
        }
        add_token(tokens, create_token(type, op_str));
    } 
    else if (op == '|') 
    {
        add_token(tokens, create_token(T_PIPE, "|"));
    }
}

void handle_env_var(const char **input, t_token **tokens) 
{
    const char *start = *input;
    while (ft_isalnum(*(*input + 1)) || *(*input + 1) == '_') 
    {
        (*input)++;
    }
    if (*input > start) 
    {
        char *val = strndup(start, *input - start + 1);
        add_token(tokens, create_token(T_DOLLAR, val));
    } else 
    {
        add_token(tokens, create_token(T_UNKNOWN, "$"));
    }
}


void print_tokens(t_token *tokens) 
{
    while (tokens) 
    {
        printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
}
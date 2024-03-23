#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROMPT "minishell$ "

typedef enum token_type {
    T_UNKNOWN,
    T_IDENTIFIER,  // Command or argument
    T_LESS,        // <
    T_GREAT,       // >
    T_LESSLESS,    // <<
    T_GREATGREAT,  // >>
    T_PIPE,        // |
    T_O_PARENT,    // (
    T_C_PARENT,    // )
    T_AND,         // &&
    T_OR,          // ||
    T_NL,          // Newline or end of input
    T_QUOTE,       // ' or " for handling quoted sections
    T_DOLLAR,      // $ for environment variables
} t_token_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// Function Prototypes
t_token *create_token(t_token_type type, const char *value);
void add_token(t_token **token_list, t_token *new_token);
void free_tokens(t_token **token_list);
void lexer(const char *input, t_token **tokens);
void print_tokens(t_token *tokens);
bool ft_isspace(char c);
void add_identifier_token(const char **start, const char *end, t_token **tokens);
void handle_quotes(const char **input, t_token **tokens, char quoteType);
void handle_operator(const char **input, t_token **tokens, char op);
void handle_env_var(const char **input, t_token **tokens);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef LEXER_H
# define LEXER_H

# define PROMPT "minishell$ "

typedef enum token_type {
    T_IDENTIFIER,    // Command or argument
    T_LESS,          // <
    T_GREAT,         // >
    T_LESSLESS,      // <<
    T_GREATGREAT,    // >>
    T_PIPE,          // |
    T_O_PARENT,      // (
    T_C_PARENT,      // )
    T_AND,           // &&
    T_OR,            // ||
    T_NL,            // Newline or end of input
    T_QUOTE,         // ' or " for handling quoted sections
    T_DOLLAR,        // $ for environment variables
}   t_token_type;

typedef struct s_token {
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;

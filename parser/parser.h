
#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_command {
    char *cmd;             // Command name
    char **args;           // Arguments, NULL-terminated array
    char *input_redirect;  // Filename for input redirection, NULL if not present
    char *output_redirect; // Filename for output redirection, NULL if not present
    bool append;           // True if output redirection should append (>>)
    struct s_command *next; // Next command in a pipeline
} t_command;

t_command *create_new_command(void);
void add_argument(t_command *cmd, char *arg);
t_command *parse_tokens(t_token *tokens);

#endif


#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdlib.h>
# include "../lexer/lexer2.h"


typedef struct s_token
{
	t_word_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_command {
    char *cmd;             // Command name
    char **args;           // Arguments, NULL-terminated array
    char *input_redirect;  // Filename for input redirection, NULL if not present
    char *output_redirect; // Filename for output redirection, NULL if not present
    bool append;           // True if output redirection should append (>>)
    struct s_command *next; // Next command in a pipeline
	char	*here_doc_filename; // Filename for here_doc, generated in here_doc.c
	t_token *tokens;
} t_command;

typedef struct s_parsed {
	t_command	*cmds;
	char		**envp;
	pid_t		pid;
} t_parsed;

t_command *create_new_command(void);
void add_argument(t_command *cmd, char *arg);
t_command *parse_tokens(t_token *tokens);

#endif

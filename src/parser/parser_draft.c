#include "parser.h"

t_command *parse_tokens(t_token *tokens)
{
    t_command *command = create_new_command();
    bool is_first_token = true;

    while (tokens != NULL)
    {
        if (tokens->type == T_IDENTIFIER)
        {
            if (is_first_token)
            {
                command->cmd = tokens->value; // First token is the command
                is_first_token = false;
            }
            else
            {
                add_argument(command, tokens->value); // Subsequent tokens are arguments
            }
        }
        // handle redirections and pipes
        tokens = tokens->next; // Move to the next token
    }
    return command;
}

//TODO: Extend the parsing logic to handle redirections (<, >, >>) and pipes (|).

/*
REDIRECTION DRAFT

while (tokens != NULL)
{
    if (tokens->type == T_IDENTIFIER)
    {
        // Command or argument handling
    }
    else if
    (tokens->type == T_LESS)
    {
        tokens = tokens->next; // Move to the filename token
        if (tokens != NULL)
        {
            command->input_redirect = tokens->value; // Set input redirection filename
        }
    }
    else if (tokens->type == T_GREAT || tokens->type == T_GREATGREAT)
    {
        tokens = tokens->next; // Move to the filename token
        if (tokens != NULL)
        {
            command->output_redirect = tokens->value; // Set output redirection filename
            command->append = (tokens->type == T_GREATGREAT); // Set append mode if >>
        }
    }
    tokens = tokens->next; // Move to the next token
}
*/

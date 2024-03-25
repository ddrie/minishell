#include "parser.h"

t_command *create_new_command(void) 
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    cmd->cmd = NULL;
    cmd->args = malloc(sizeof(char*)); // allocate space for at least a NULL terminator
    if (!cmd->args) 
    {
        free(cmd);
        return NULL;
    }
    cmd->args[0] = NULL; // Initialize args array as empty
    cmd->input_redirect = NULL;
    cmd->output_redirect = NULL;
    cmd->append = false;
    cmd->next = NULL;

    return cmd;
}

void add_argument(t_command *cmd, char *arg) 
{
    int i = 0;
    while (cmd->args[i] != NULL) i++; 

    // Reallocate args array to accommodate one more argument + NULL terminator
    char **new_args = realloc(cmd->args, sizeof(char*) * (i + 2));
    if (!new_args) return; // Handle allocation failure

    cmd->args = new_args;
    cmd->args[i] = arg; // Add the new argument
    cmd->args[i + 1] = NULL; // Ensure NULL termination
}

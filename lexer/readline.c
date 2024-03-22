#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while (1) 
    {
        input = readline("minishell> ");
    
        if (!input)
            break;
        if (*input)
            add_history(input);

        printf("You entered: %s\n", input);
        free(input);
    }

    printf("\nExiting Minishell...\n");
    return 0;
}

// tokens: commands, args, ops
// commands: ◦ echo with option -n, 
//cd with only a relative or absolute path 
//pwd with no options
//export with no options 
//unset with no options
//env with no options or arguments
//exit with no options
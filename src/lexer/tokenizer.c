
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int count_tokens(const char *input)
{
    int tokens = 0;
    bool in_token = false;
    int i = 0;
    while (input[i] != '\0')
    {
        if (input[i] != ' ' && !in_token)
        {
            tokens++;
            in_token = true;
        }
        else if (input[i] == ' ')
        {
            in_token = false;
        }
        i++;
    }

    return tokens;
}

char **tokenizer(const char *input) {
    bool in_single_quote = false;
    bool in_double_quote = false;
    int token_count = count_tokens(input);
    char **tokens = calloc(token_count + 1, sizeof(char *));
    if (!tokens) return NULL;

    const char *token_start = input;
    int i = 0, current_token_index = 0;
    int j = 0;

    while (input[i] != '\0')
    {
        bool at_end_of_token = false;

        if (input[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        }
        else if (input[i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }

        if ((input[i] == ' ' && !in_single_quote && !in_double_quote) || (input[i + 1] == '\0' && !(input[i] == ' ' && !in_single_quote && !in_double_quote)))
        {
            at_end_of_token = true;
            int token_len = (i - (token_start - input)) + (input[i + 1] == '\0' ? 1 : 0);
            char *token = malloc(token_len + 1);
            if (!token)
            {
                while(j < current_token_index)
                {
                    free(tokens[j]);
                    j++;
                }
                free(tokens);
                return NULL;
            }
            strncpy(token, token_start, token_len);
            token[token_len] = '\0';
            tokens[current_token_index++] = token;
            token_start = input + i + 1;
        }
        i++;
    }

    tokens[current_token_index] = NULL;
    return tokens;
}

/* int main()
{
    const char *input = "\"This is\" a 'test input' string' lol";
    char **tokens = tokenizer(input);

    for (int i = 0; tokens && tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]);
    }
    free(tokens);

    return 0;
} */

// command
// command arguments


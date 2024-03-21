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

char **tokenizer(const char *input) 
{
    int token_count = count_tokens(input);
    char **tokens = calloc(token_count + 1, sizeof(char *));
    if (!tokens) return NULL;

    int i = 0;
    int j = 0;
    int current_token_index = 0;
    const char *token_start = input;
    int token_len = 0;
    char *token = malloc(token_len + 1);

    while (input[i] != '\0') 
    {
        if (input[i] == ' ' || input[i + 1] == '\0') 
        {
            // Adjust token length for last token
            token_len = input[i + 1] == '\0' && input[i] != ' ' ? token_len + 1 : token_len;

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

            token_start = input + i + 1; // Update token_start to the next character after space
            token_len = 0; // Reset token length for the next token
        } 
        else 
            token_len++; // Increment token length if the current character is not a space
        i++; // Move to the next character
    }

    tokens[current_token_index] = NULL;
    return tokens;
}

int main() 
{
    const char *input = "This is a test input string";
    char **tokens = tokenizer(input);

    for (int i = 0; tokens && tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]); // Free each token
    }
    free(tokens); // Free the array of tokens

    return 0;
}


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

bool update_token_state(char c, bool *in_single_quote, bool *in_double_quote) 
{
    if (c == '\'' && !*in_double_quote) 
    {
        *in_single_quote = !*in_single_quote;
        return true;
    } 
    else if (c == '\"' && !*in_single_quote) 
    {
        *in_double_quote = !*in_double_quote;
        return true; 
    }
    return false;
}

bool add_token(const char *input, int *start_index, int end_index, char ***tokens, int *token_count) 
{
    int token_len = end_index - *start_index + 1;
    int token_len = input[i + 1] == '\0' && input[i] != ' ' ? token_len + 1 : token_len;

    char *token = malloc(token_len + 1);
    if (!token) 
    {
        return false;
    }

    strncpy(token, &input[*start_index], token_len);
    token[token_len] = '\0';
    (*tokens)[(*token_count)++] = token;
    *start_index = end_index + 1;
    return true;
}

char **tokenizer(const char *input) 
{
    bool in_single_quote = false, in_double_quote = false;
    int token_count = count_tokens(input);
    char **tokens = calloc(token_count + 1, sizeof(char *));
    int i = 0;
    int j = 0;
    int start_index = 0
    int current_token_count = 0;
    if (!tokens) return NULL;

    
    while (input[i] != '\0')
    {
        if (update_token_state(input[i], &in_single_quote, &in_double_quote)) continue;
        
        if ((input[i] == ' ' && !(in_single_quote || in_double_quote)) || input[i+1] == '\0') 
        {
            if (input[i+1] == '\0' && !(input[i] == ' ')) i++;
            if (!add_token(input, &start_index, i, &tokens, &current_token_count)) 
            {
                while(j < current_token_count)
                {
                    free(tokens[j]);
                    j++;
                }
                free(tokens);
                return NULL;
            }
        }
        i++;
    }

    tokens[current_token_count] = NULL;
    return tokens;
}

int main() 
{
    const char *input = "\"This is\" a 'test input' string' lol";
    char **tokens = tokenizer(input);

    for (int i = 0; tokens && tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]); 
    }
    free(tokens); 

    return 0;
}
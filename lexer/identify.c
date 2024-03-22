#include "lexer.h" 

void add_char_to_dynamic_string(char **str, int *capacity, int *size, char c) {
    if (*size + 1 >= *capacity) {
        *capacity *= 2;
        *str = realloc(*str, *capacity);
    }
    (*str)[(*size)++] = c;
    (*str)[*size] = '\0'; 

void identify(const char *input, t_token **tokens) 
{
    char *current_str = NULL;
    int capacity = 10, size = 0;
    current_str = malloc(capacity);
    current_str[0] = '\0';

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (isspace(c) || c == '<' || c == '>' || c == '|' || c == '\0') 
        {
            if (size > 0) 
            {
                add_token(tokens, create_token(T_IDENTIFIER, current_str));
                free(current_str); 
                current_str = malloc(capacity = 10);
                size = 0;
                current_str[0] = '\0';
            }
            if (isspace(c)) continue;
            // Handling for other delimiters like '<', '>', '|' can go here
        } else 
        {
            // Part of an identifier, accumulate characters
            add_char_to_dynamic_string(&current_str, &capacity, &size, c);
        }
    }

    // Handle the last identifier if there is one
    if (size > 0) {
        add_token(tokens, create_token(T_IDENTIFIER, current_str));
    }
    free(current_str);
}

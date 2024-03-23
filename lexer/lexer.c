#include "lexer.h" 
#include "../libft/libft.h"

void add_identifier_token(const char **start, const char *end, t_token **tokens) {
    if (*start < end) {
        char *val = strndup(*start, end - *start);
        add_token(tokens, create_token(T_IDENTIFIER, val));
        // No need to free val here since create_token now takes ownership
    }
}

void lexer_recursive(const char *input, const char *start, t_token **tokens) 
{
    if (!*input) 
    {
        add_identifier_token(&start, input, tokens);
        return;
    }

    if (*input == '<' || *input == '>') 
    {
        add_identifier_token(&start, input, tokens);
        handle_operator(&input, tokens, *input);
    } 
    else if (*input == '|') 
    {
        add_identifier_token(&start, input, tokens);
        handle_operator(&input, tokens, *input);
    } 
    else if (ft_isspace(*input)) 
    {
        add_identifier_token(&start, input, tokens);
        start = input + 1;
    }
     else if (*input == '$') 
    {
        add_identifier_token(&start, input, tokens); 
        handle_env_var(&input, tokens);
        start = input + 1;
    }
    lexer_recursive(input + 1, start, tokens);
}

void lexer(const char *input, t_token **tokens) 
{
    lexer_recursive(input, input, tokens);
}

int main() {
    const char *input = "cat < input.txt > output.txt | grep 'something'";
    t_token *tokens = NULL;
    lexer(input, &tokens);
    print_tokens(tokens);
    free_tokens(&tokens);
    return 0;
}
#include "lexer.h"
#include "../libft/libft.h"

t_token *create_token(t_token_type type, const char *value) 
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) 
    {
        perror("Failed to allocate memory for token");
        exit(EXIT_FAILURE);
    }
    new_token->type = type;
    new_token->value = value ? ft_strdup(value) : NULL; 
    new_token->next = NULL;
    return new_token;
}

void add_token(t_token **token_list, t_token *new_token) 
{
    if (!*token_list) 
    {
        *token_list = new_token;
    } else 
    {
        t_token *temp = *token_list;
        while (temp->next) 
        {
            temp = temp->next;
        }
        temp->next = new_token;
    }
}

void free_tokens(t_token **token_list) 
{
    t_token *temp;
    while (*token_list) 
    {
        temp = (*token_list)->next;
        free((*token_list)->value);
        free(*token_list);
        *token_list = temp;
    }
}

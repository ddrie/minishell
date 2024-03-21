void parse_input(char *input) 
{
    char **tokens = ...; // Initialize your tokens array
    int token_count;
    bool in_single_quote;
    bool in_double_quote;
    int i;
    char    current_char;

    i = 0;
    token_count = 0;
    in_single_quote = false;
    bin_double_quote = false;


    while (input[i] != '\0')
    {
     current_char = input[i];

        // Toggle quote states
        if (current_char == '\'' && !in_double_quote) 
        {
            in_single_quote = !in_single_quote;
            continue; // Don't include the quote char in the token
        } 
        else if (current_char == '\"' && !in_single_quote) 
        {
            in_double_quote = !in_double_quote;
            continue; // Don't include the quote char in the token
        }

        i++;
    }

        // Add logic here to handle the current_char based on the state
        // This includes appending chars to the current token,
        // handling escaped characters, etc.
    

    // Finalize tokenization based on the states and characters encountered
}

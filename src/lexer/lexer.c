/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:30:07 by cgray             #+#    #+#             */
/*   Updated: 2024/03/28 17:41:50 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer2.h"

int	expand_variable_in_word(t_word *word, t_envp *envp_list)
{
	char	*variable;
	int		i;

	i = 0;
	while (word->cont && word->cont[i])
	{
		//don't think this works
		if (word->cont[i] == '$' && word->cont[i + 1]
			&& word->cont[i + 1] == '?')
		{
			variable = ft_itoa(42); //placeholder number for exit code
			free(word->cont);
			word->cont = ft_strdup(variable);
			free(variable);
		}
		//quotes?
		else if (word->cont[i] == '$' && word->cont[i + 1])
		{
			variable = find_key(envp_list, word->cont + i + 1, &i);
			if (variable)
			{
				i = ft_strlen(variable);
				free(word->cont);
				word->cont = ft_strdup(variable);
			}
			else
				return (0);
		}
		else
			i++;
	}
	return (1);
}

/* iterates through words expanding each word with envp var */
int	expand_variables(t_split *split, t_envp *envp_list)
{
	t_word	*word;

	word = split->first;
	while (word)
	{
		expand_variable_in_word(word, envp_list);
		word = word->next;
	}
	return (0);
}

/* creates word struct from input cmd and type */
t_word	*create_word(char *cmd, int type)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->cont = ft_strdup(cmd);
	word->type = type;
	word->next = NULL;
	word->prev = NULL;
	return (word);
}

/* calls create_word and sets relevant split vars */
int	push_word(t_split *split, char *cmd, int type)
{
	t_word	*word;

	word = create_word(cmd, type);
	if (!word)
		return (0);
	word->index = split->n_cmds;
	word->next = NULL;
	word->prev = split->last;
	if (split->n_cmds == 0)
		split->first = word;
	else
		split->last->next = word;
	split->last = word;
	split->n_cmds++;
	return (1);
}

/* checks for '|' '>' '<', returns 1 if found */
int	is_type_sym(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

/* returns len of string in place, delin by spaces/type sym */
int	strlen_in_place(char *input, int *i)
{
	int	len;
	int	start;

	start = *i;
	while (input[*i] && !is_type_sym(input[*i]) || ft_isspace(input[*i]))
		(*i)++;
	len = *i - start;
	return (len);
}

/* adds simple string type to split struct */
int	add_string(char *input, int *i, t_split *split)
{
	int		start;
	int		len;
	int		j;
	char	*str;
	int		exit;

	start = *i;
	len = strlen_in_place(input, i);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (1);
	j = 0;
	while (start + j < *i)
	{
		str[j] = input[start + j];
		j++;
	}
	// str[j] = '\0';
	exit = push_word(split, str, STR);
	if (!exit)
		return (0);
	free(str);
	return (1);
}

/* checks if redirection sym is doubled for heredoc or
regular redirection */
int	add_redirection(char *input, int *i, t_split *split)
{
	int exit;

	exit = 0;
	if (input[*i + 1] && input[*i + 1] == input[*i])
	{
		if (input[*i] == '<')
			exit = push_word(split, "<<", REDIR);
		else
			exit = push_word(split, ">>", REDIR);
		*i = *i + 2;
	}
	else
	{
		if (input[*i] == '>')
			exit = push_word(split, ">", REDIR);
		else
			exit = push_word(split, "<", REDIR);
		*i = *i + 1;
	}
	return (exit);
}

/* assigns command type simply by checking syms */
int	get_word_type(char *input, int *i, t_split *split)
{
	int	exit;

	exit = 0;
	if (input[*i] == '|')
	{
		exit = push_word(split, "|", PIPE);
		(*i)++;
	}
	else if (input[*i] == '>' || input[*i] == '<')
	{
		exit = add_redirection(input, i, split);
	}
	else
	{
		exit = add_string(input, i, split);
	}
	return (exit);
}

/* skips spaces in place */
void	skip_spaces(char *input, int *j)
{
	int	i;

	i = *j;
	while (input[i] && ft_isspace(input[i]))
		i++;
	*j = i;
}

/* splits string into words with spaces as delin
calls get_word_type to put into struct */
int	split_words(char *input, t_split *split)
{
	int	i;

	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (input[i])
		{
			if (!get_word_type(input, &i, split))
				return (0);
		}
	}
	return (1);
}

/* checks order of commands in split struct */
int	split_verify(t_split *split)
{
	t_word	*word;

	word = split->first;
	if (word && word->type == PIPE)
	{
		ft_putstr_fd("first cmd cannot be pipe '|'\n", 2);
		return (0);
	}
	if (word && split->last->type == PIPE)
	{
		ft_putstr_fd("last cmd cannot be pipe '|'\n", 2);
		return (0);
	}
	while (word)
	{
		if (word->type == REDIR && (word->next && word->next->type == REDIR)
			|| word->type == PIPE && (word->next && word->next->type == PIPE))
		{
			ft_putstr_fd("Cannot have two consecutive '", 2);
			ft_putstr_fd(word->cont, 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
		word = word->next;
	}
	return (1);
}

/* assigns word type to each word in split struct */
void	split_types(t_split *split)
{
	t_word	*word;

	word = split->first;
	if (word && word->type == STR)
		word->type = CMD;
	while (word)
	{
		if (word->prev && word->type == STR && word->prev->type == PIPE)
			word->type = CMD;
		else if (word->prev && word->prev->type == REDIR)
			word->type = PATH;
		else if (word->type == STR)
			word->type = ARG;
		word = word->next;
	}
}

/* iterates thru split struct, freeing each element */
void	free_split(t_split *split)
{
	t_word	*word;
	t_word	*tmp;

	if (!split)
		return ;
	word = split->first;
	while (word)
	{
		free(word->cont);
		tmp = word;
		word = word->next;
		free(tmp);
	}
	free(split);
}

/* splits input string into tokens. splits based on spaces,
expands envp variables and sorts split struct into commands */
t_split	*split_input_str(char *input, t_envp *envp_list)
{
	t_split	*split;
	int		exit;

	exit = 0;
	split = (t_split *)malloc(sizeof(t_split));
	if (!split)
		return (NULL);
	//need error checking for each of these
	split_words(input, split);
	split_verify(split);
	expand_variables(split, envp_list);
	//quote_handling(split);
	//
	split_types(split);
	return (split);
}

int main(int ac, char **av, char **envp)
{
	// char *input = "$USER | ls -l | cat -e > output.txt < input.txt";
	char *input = av[1];
	t_envp *envp_list;
	t_split *split;
	t_word *ptr;

	(void)ac;
	envp_list = fill_envp(envp);
	split = split_input_str(input, envp_list);
	ptr = split->first;
	while (ptr)
	{
		printf("%i. ", ptr->index);
		printf("%s", ptr->cont);
		if (ptr->type == CMD)
			printf(" - CMD\n");
		else if (ptr->type == REDIR)
			printf(" - REDIR\n");
		else if (ptr->type == PATH)
			printf(" - PATH\n");
		else if (ptr->type == PIPE)
			printf(" - PIPE\n");
		else if (ptr->type == QUOTE)
			printf(" - QUOTE\n");
		else if (ptr->type == ARG)
			printf(" - ARG\n");
		else if (ptr->type == STR)
			printf(" - STR\n");
		ptr = ptr->next;
	}
}

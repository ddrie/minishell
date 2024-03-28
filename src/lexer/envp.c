/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:23:08 by cgray             #+#    #+#             */
/*   Updated: 2024/03/28 17:26:30 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_formatter(char *path, char *cmd)
{
	char	*path_formatted;
	char	*add_slash;

	add_slash = ft_strjoin(path, "/");
	path_formatted = ft_strjoin(add_slash, cmd);
	free(add_slash);
	return (path_formatted);
}

/* iterates through list and returns string value corresponding to the key
*i is modified to use index later in expand_variables*/
char	*find_key(t_envp *envp_list, char *key, int *i)
{
	t_envp	*current;
	char	*str;
	char	*temp_key;

	current = envp_list;
	while (current)
	{
		//THIS COULD BREAK IF *KEY CONTAINS MORE THAN JUST THE KEY, NEED TO CHECK BASH BEHAVIOR
		temp_key = ft_strndup(key, ft_strlen(current->key)); //if key starts with current->key
		if (ft_strncmp(current->key, temp_key, ft_strlen(key)) == 0)
		{
			*i = ft_strlen(key);
			str = ft_strdup(current->value);
			return (str);
		}
		free(temp_key);
		current = current->next;
	}
	free(temp_key);
	free(current);
	return (NULL);
}

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*path_finder(t_envp *envp_list, char *cmd)
{
	char	**paths_tab;
	char	*path;
	int		i;

	paths_tab = ft_split(find_key(envp_list, "PATH", NULL), ':');
	i = 0;
	while (paths_tab[i])
	{
		path = path_formatter(paths_tab[i], cmd);
		if (access(path, F_OK) == 0)
		{
			free_tab(paths_tab);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(paths_tab);
	return (NULL);
}


/* allocates new t_envp struct and fills from envp string */
t_envp	*new_envp(char *envp_line)
{
	t_envp	*new;
	char	*from_equal;
	int		key_len;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	from_equal = ft_strchr(envp_line, '=');
	if (!from_equal)
	{
		return (NULL);
	}
	key_len = from_equal - envp_line;
	new->key = ft_strndup(envp_line, key_len);
	new->value = ft_strdup(from_equal + 1);
	new->next = NULL;
	return (new);
}

/* fills linked list of envp structs */
t_envp	*fill_envp(char **envp)
{
	t_envp	*node;
	t_envp	*top;
	t_envp	*end;
	int		i;

	i = 0;
	top = NULL;
	end = NULL;
	while (envp[i])
	{
		node = new_envp(envp[i]);
		if (!node)
			return (NULL);
		if (!top)
			top = node;
		else
			end->next = node;
		end = node;
		i++;
	}
	end->next = NULL;
	return (top);
}

/* int main(int argc, char **argv, char **envp)
{
	t_envp	*envp_list;
	const char	*input;
	t_token		*tokens;

	(void)argc, (void)argv;
	envp_list = fill_envp(envp);
	input = "$USER < input.txt > output.txt | grep 'something' '$HOME' $PWD";
	tokens = NULL;
	lexer(input, &tokens);
	expand_variables(&tokens, envp_list);
	print_tokens(tokens);
	free_tokens(&tokens);
	// while (envp_list)
	// {
	// 	printf("Key: %s: Value: %s\n", envp_list->key, envp_list->value);
	// 	envp_list = envp_list->next;
	// }
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:30:27 by cgray             #+#    #+#             */
/*   Updated: 2024/03/28 17:07:06 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER2_H
# define LEXER2_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../../lib/Libft/includes/libft.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_redir
{
	char			*path;
	int				type;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmds
{
	char			*command;
	char			**args;
	t_redir			*redirections;
	struct s_cmds	*next;
	// int				(*builtin)(t_utils *, t_cmds *);
	struct s_cmds	*prev;
	char			*hd_file_name;
}	t_cmds;

typedef struct s_utils
{
	t_cmds	*cmds;
	char			*input;
	char			**envp;
	char			**paths;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	bool			reset;
	bool			heredoc;
}	t_utils;

typedef struct s_word
{
	char			*cont;
	int				index;
	int				type;
	struct s_word		*next;
	struct s_word		*prev;
}	t_word;

typedef struct s_split
{
	int		n_cmds;
	t_word	*first;
	t_word	*last;
}	t_split;


typedef enum e_word_type
{
	CMD,
	FLAG,
	REDIR,
	PATH,
	PIPE,
	QUOTE,
	ARG,
	STR,
}	t_word_type;

t_envp	*fill_envp(char **envp);
char	*find_key(t_envp *envp_list, char *key, int *i);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:26:32 by cgray             #+#    #+#             */
/*   Updated: 2024/03/26 15:36:32 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../lib/Libft/includes/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"


typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

void	expand_variables(t_token **tokens, t_envp *envp_list);
char	*find_key(t_envp *envp_list, char *key);

#endif

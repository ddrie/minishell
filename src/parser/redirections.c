/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:04:18 by cgray             #+#    #+#             */
/*   Updated: 2024/03/26 16:10:07 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* all of these are untested so far */

int	handle_outfile(t_token *redir)
{
	int	fd;

	if (redir->type == T_GREATGREAT) //heredoc
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) //infile error, doesn't exist/no permissions
	{
		ft_putstr_fd("minishell: input file error.\n", 2);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: cannot create pipe.\n", 2);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0) //infile error, doesn't exist/no permissions
	{
		ft_putstr_fd("minishell: input file error.\n", 2);
		return (EXIT_FAILURE);
	}
	// create pipe between fd and STDIN
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: cannot create pipe.\n", 2);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirection(t_token *cmd)
{
	while (cmd)
	{
		if (cmd->type == T_LESS)
			handle_infile(cmd->next->value); //send filename
		else if (cmd->type == T_GREAT
			|| cmd->type == T_GREATGREAT)
			handle_outfile(cmd->next); //send redirection
		else if (cmd->type == T_LESSLESS)
			// handle_infile(here_doc_filename);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

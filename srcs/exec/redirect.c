/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-23 08:07:41 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-23 08:07:41 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_trunc(t_token *token, int *saved_stdout)
{
	int			fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '>'");
		exit(EXIT_FAILURE);
	}
	fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_append(t_token	*token, int *saved_stdout)
{
	int	fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '>>'");
		exit(EXIT_FAILURE);
	}
	fd = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_input(t_token *token)
{
	int	fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '<'");
		exit(EXIT_FAILURE);
	}
	fd = open(token->str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	restore_stdout(int *saved_stdout)
{
	if (*saved_stdout != -1)
	{
		dup2(*saved_stdout, STDOUT_FILENO);
		close(*saved_stdout);
		*saved_stdout = -1;
	}
}

void	handle_redirections(t_token *token, t_exec *exec)
{
	while (token)
	{
		if (token->index == TRUNC)
			redirect_trunc(token, &exec->saved_stdout);
		else if (token->index == APPEND)
			redirect_append(token, &exec->saved_stdout);
		else if (token->index == INPUT)
			redirect_input(token);
		else if (token->index == HEREDOX)
			here_doc(token->next->str);
		token = token->next;
	}
}

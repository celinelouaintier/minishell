/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:07:41 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/18 14:15:53 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_trunc(t_token *token, int *saved_stdout)
{
	int			fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '>'");
		return (-1);
	}
	fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_append(t_token	*token, int *saved_stdout)
{
	int	fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '>>'");
		return (-1);
	}
	fd = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_input(t_token *token)
{
	int	fd;

	token = token->next;
	if (!token || !token->str)
	{
		perror("expected file after '<'");
		return (-1);
	}
	fd = open(token->str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
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

int	handle_redirections(t_token *token, t_exec *exec)
{
	while (token)
	{
		if (token->index == TRUNC
			&& redirect_trunc(token, &exec->saved_stdout) == -1)
			return (-1);
		else if (token->index == APPEND
			&& redirect_append(token, &exec->saved_stdout) == -1)
			return (-1);
		else if (token->index == INPUT && redirect_input(token) == -1)
			return (-1);
		else if (token->index == HEREDOX)
			here_doc(token->next->str);
		token = token->next;
	}
	return (0);
}

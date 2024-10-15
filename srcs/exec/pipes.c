/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 15:38:45 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-14 15:38:45 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipes(t_token *cmd, char *envp[])
{
	char	**args;
	t_token	*tmp;
	char	*path;

	tmp = cmd;
	path = get_command_path(cmd->str);
	
	if (execve(path, args, envp) == -1)
	{
		perror("Error");
		free(path);
		ft_free(args);
		exit(1);
	}
}

// int	open_files(t_token *token)
// {
// 	int	fd;

// 	while (token)
// 	{
// 		if (token->index == INPUT )
// 		{
// 			fd = open(token->next->str, O_RDONLY, 0777);
// 			if (fd < 0)
// 			{
// 				perror("Error");
// 				return (-1);
// 			}
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (token->index == TRUNC)
// 		{
// 			fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd < 0)
// 			{
// 				perror("Error");
// 				return (-1);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }

void	process_pipes(t_token *token, char *env[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_pipes(token, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

// void	init_pipes(t_token *token, char *env[])
// {
// 	int	pipe_fd[2];

// 	while (token)
// 	{
// 		if (token->next && token->next->index == PIPE)
// 		{
// 			if (pipe(pipe_fd) == -1)
// 			{
// 				perror("pipe");
// 				exit(1);
// 			}
// 		}
// 		else
// 			pipe_fd[0] = -1;
// 		token = token->next;
// 	}
// }



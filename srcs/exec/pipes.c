/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:38:45 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/22 14:02:58 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **args, char *env[])
{
	char	*path;

	path = get_command_path(args[0]);
	if (!path)
	{
		perror("Command not found");
		ft_free(args);
		exit(EXIT_FAILURE);
	}
    if (execve(path, args, env) == -1) {
        perror("Error");
        free(path);
        ft_free(args);
        exit(EXIT_FAILURE);
    }
	free(path);
}

int	**create_pipes(int	pipes_num)
{
	int	i;
	int	**pipe_fd;

	pipe_fd = malloc(sizeof(int *) * pipes_num);
	if (!pipe_fd)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < pipes_num)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fd);
}

void	close_pipes(int **pipes_fd, int pipes_num, int cmd)
{
	int	i;

	i = 0;
	while (i < pipes_num)
	{
		if (i != cmd -1)
			close(pipes_fd[i][0]);
		if (i != cmd)
			close(pipes_fd[i][1]);
		i++;
	}
}

void	fork_pipes(t_token *token, int **pipe_fd, int pipes_num, char *env[])
{
	pid_t	pid;
	char	**args;
	int		i;

	i = 0;
	while (token)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (!pid)
		{
			if (i > 0)
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			if (i < pipes_num)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			close_pipes(pipe_fd, pipes_num, i);
			args = init_args(token);
			exec(args, env);
		}
		while (token && token->index != PIPE)
			token = token->next;
		token = token ? token->next : token;
		i++;
	}
}

void	process_pipes(t_token *token, char *env[])
{
	int	pipes_num;
	int	**pipe_fd;
	int	i;

	pipes_num = count_pipes(token);
	pipe_fd = create_pipes(pipes_num);
	i = 0;
	fork_pipes(token, pipe_fd, pipes_num, env);
	while (i < pipes_num)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
	while (wait(NULL) > 0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:38:45 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/25 19:03:40 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **args, t_env **env)
{
	char	*path;
	char	**envp;

	if (access(args[0], X_OK) != 0)
		path = get_command_path(args[0]);
	else
		path = args[0];
	if (!path)
	{
		perror("Command not found");
		ft_free(args);
		exit(EXIT_FAILURE);
	}
	envp = lst_to_array(env);
	if (execve(path, args, envp) == -1)
	{
		perror("Error");
		free(path);
		ft_free(args);
		exit(EXIT_FAILURE);
	}
	free(path);
}

int	**create_pipes(int pipes_num)
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
		if (i != cmd - 1)
			close(pipes_fd[i][0]);
		if (i != cmd)
			close(pipes_fd[i][1]);
		i++;
	}
}

void	cmd_sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\n");
	else if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
}

void	fork_pipes(t_token *token, t_exec *exec, t_env **envp)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (token)
	{
		signal(SIGQUIT, cmd_sig_handler);
		signal(SIGINT, cmd_sig_handler);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (!pid)
			child_process(token, exec, i, envp);
		if (i > 0)
			close(exec->pipe_fd[i - 1][0]);
		if (i < exec->pipe_num)
			close(exec->pipe_fd[i][1]);
		while (token && token->index != PIPE)
			token = token->next;
		if (token && token->index == PIPE)
			token = token->next;
		i++;
	}
}

void	process_pipes(t_token *token, t_env **envp)
{
	int		i;
	t_exec	exec;
	pid_t	pid;

	exec.pipe_num = count_pipes(token);
	exec.pipe_fd = create_pipes(exec.pipe_num);
	exec.saved_stdout = -1;

	i = 0;
	fork_pipes(token, &exec, envp);
	while (i < exec.pipe_num)
	{
		close(exec.pipe_fd[i][0]);
		close(exec.pipe_fd[i][1]);
		free(exec.pipe_fd[i]);
		i++;
	}
	free(exec.pipe_fd);
	while ((pid = wait(NULL)) > 0)
		;
}

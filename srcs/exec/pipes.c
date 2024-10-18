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
	for (int i = 0; args[i] != NULL; i++)
    {
        ft_printf("arg[%d]: %s\n", i, args[i]);
    }
    if (execve(path, args, env) == -1) {
        perror("Error");
        free(path);
        ft_free(args);
        exit(EXIT_FAILURE);
    }
	free(path);
}

void	process_pipes(t_token *token, char *env[])
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2] = {-1, -1};
	pid_t	pid;
	int		has_pipe;
	int		is_first_cmd = 1;
	char	**args;

	while (token)
	{
		has_pipe = 0;
		if (token->index == PIPE)
			has_pipe = 1;
		if (has_pipe && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (!pid)
		{
			if (!is_first_cmd)
			{
				if (prev_pipe_fd[0] != -1)
				{
					// close(prev_pipe_fd[1]);
					dup2(prev_pipe_fd[0], STDIN_FILENO); //lecture depuis le pipe precedent
					close(prev_pipe_fd[0]);
				}
			}
			if (has_pipe)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO); // rediriger vers le pipe
				close(pipe_fd[1]);
			}
			args = init_args(token);
			exec(args, env);
		}
		else
		{
			if (has_pipe)
				close(pipe_fd[1]);
			if (prev_pipe_fd[0] != -1)
				close(prev_pipe_fd[0]);
		}
		if (has_pipe)
		{
			prev_pipe_fd[0] = pipe_fd[0];
		}
		while (token && token->index != PIPE)
			token = token->next;
		if (token && token->index == PIPE)
			token = token->next;
		is_first_cmd = 0;
	}
	while(wait(NULL) > 0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 14:04:17 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-29 14:04:17 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter)
{
	int		is_limiter;
	char	*line;

	is_limiter = 0;
	while (!is_limiter)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			is_limiter = 1;
	}
	// close(*exec->pipe_fd[1]);
}

// void	here_doc(char *limiter, t_exec *exec)
// {
// 	pid_t	pid;

// 	if (pipe(*exec->pipe_fd) == -1)
// 		exit(1);
// 	pid = fork();
// 	if (!pid)
// 		find_limiter(limiter, exec);
// 	else
// 	{
// 		close(*exec->pipe_fd[1]);
// 		dup2(*exec->pipe_fd[0], STDIN_FILENO);
// 		close(*exec->pipe_fd[0]);
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:04:17 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/01 21:11:29 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_here_doc(void)
{
	int	fd;

	fd = open(".here_doc.tmp", O_RDONLY);
	if (fd == -1)
	{
		perror(".here_doc.tmp file open failure");
		unlink(".here_doc.tmp");
	}
	return (fd);
}

void	find_limiter(char *limiter, int is_limiter, int fd)
{
	char	*line;

	while (!is_limiter)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			is_limiter = 1;
			free(line);
		}
		else
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
	}
}

void	here_doc(char *limiter)
{
	int		is_limiter;
	int		fd;

	is_limiter = 0;
	fd = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	find_limiter(limiter, is_limiter, fd);
	close(fd);
	fd = open_here_doc();
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".here_doc.tmp");
}

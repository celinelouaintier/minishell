/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:04:17 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/31 13:17:59 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_here_doc(void)
{
    int fd;

    fd = open(".here_doc.tmp", O_RDONLY);
    if (fd == -1)
    {
        perror(".here_doc.tmp file open failure");
        unlink(".here_doc.tmp");
    }
    return fd;
}

void	here_doc(char *limiter)
{
	int		is_limiter;
	char	*line;
	int		fd;

	is_limiter = 0;
	fd = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
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
	close(fd);
	fd = open_here_doc();
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".here_doc.tmp");
}


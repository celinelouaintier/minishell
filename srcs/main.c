/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-01 14:27:34 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-01 14:27:34 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	find_limiter(char *limiter, int pipe_fd[2])
// {
// 	int		is_limiter;
// 	char	*line;

// 	close(pipe_fd[0]);
// 	is_limiter = 0;
// 	while (!is_limiter)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			is_limiter = 1;
// 			exit(0);
// 		}
// 		write(pipe_fd[1], line, ft_strlen(line));
// 	}
// 	close(pipe_fd[1]);
// }


int main(void)
{
	char	*line;
	HIST_ENTRY **hist;

	line = ft_strdup("");
	hist = malloc(sizeof(HIST_ENTRY**));
	while (ft_strncmp(line, "exit", 5))
	{
		line = readline("Minishell> ");
		ft_printf("%s\n", line);
		add_history(line);
	}
	ft_printf("%s\n", hist[1]->line);
	return 0;
}


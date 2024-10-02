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
	int		hist_size;
	int		hist_count;
	char	**hist;
	char	**new_hist;

	line = ft_strdup("");
	hist_size = 10;
	hist_count = 0;
	hist = malloc(sizeof(char*) * hist_size);
	while (ft_strncmp(line, "exit", 5))
	{
		line = readline("Minishell> ");
		add_history(line);
		if (hist_count >= hist_size)
		{
			hist_size *= 2;
			new_hist = malloc(sizeof(char *) * hist_size);
			ft_memcpy(new_hist, hist, hist_count * sizeof(char *));
			hist = new_hist;
		}
		hist[hist_count++] = ft_strdup(line);
	}
	for (int i = 0; i < hist_count; i++)
		ft_printf("%s\n", hist[i]);
	return 0;
}


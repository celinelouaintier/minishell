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

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char	*get_command_path(char *command)
{
	int		i;
	// char	*tmp_path;
	char	*full_path;
	char	*paths;

	paths = "srcs/";
	i = 0;
	// tmp_path = ft_strjoin(paths[i], "/");
	full_path = ft_strjoin(paths, command);
	// free(tmp_path);
	if (!access(full_path, X_OK))
	{
		ft_printf("Here !");
		// free(paths);
		return (full_path);
	}
	// free(full_path);
	// while (paths[++i])
	// {
	// }
	// free(paths);
	return (NULL);
}

int main(int ac, char **av)
{
	char	*line;
	char	*path;
	char	**command;
	// int i = 0;

	(void)ac;
	(void)av;
	line = ft_strdup("");
	while (ft_strncmp(line, "exit", 5))
	{
		line = readline("Minaim> ");
		command = ft_split(line, ' ');
		char *newargv[] = {NULL, command[0], command[1], "1", "0", NULL};
		add_history(line);
		path = "./commands";
		newargv[0] = path;
		if (execve(path, newargv, NULL) == -1 && ft_strncmp(line, "exit", 5) && ft_strncmp(line, "", 2))
		{
			perror("Error");
			// free(path);
			free(line);
		}
		// i++;
	}
	// for (int i = 0; i < hist_count; i++)
		
	return 0;
}


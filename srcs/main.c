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

// char **parse(char *line)
// {

// 	return (parse);
// }

int main(int ac, char **av)
{
	char	*line;
	char	*path;
	char	*pwd;
	char	**command;
	pid_t	pid;

	(void)ac;
	(void)av;
	line = ft_strdup("");
	// data = malloc(sizeof(t_data));
	// getcwd(pwd, sizeof(pwd));
	// pwd = ft_strdup();
	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	while (ft_strncmp(line, "exit", 5))
	{
		line = readline("Minaim> ");
		command = ft_split(line, ' ');
		char *newargv[] = {NULL, command[0], command[1], "1", "0", NULL};
		char *env[] = {pwd, NULL};
		add_history(line);
		path = "./commands";
		newargv[0] = path;
		pid = fork();
		if (!pid)
		{
			if (execve(path, newargv, env) == -1 && ft_strncmp(line, "exit", 5) && ft_strncmp(line, "", 2))
			{
				perror("Error");
				// free(path);
				free(line);
			}
		}
		else
			wait(NULL);
	}		
	return 0;
}


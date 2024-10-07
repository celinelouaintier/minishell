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


void	exec(char **cmd, char *envp[], char *line)
{
	char	*path;
	char	*newargv[] = {NULL, cmd[0], cmd[1], "1", "0", NULL};

	path = "/home/clouaint/cercle_3/minishell/Minaim/commands";
	newargv[0] = cmd[0];
	if (execve(path, newargv, envp) == -1 && ft_strncmp(line, "exit", 5) && ft_strncmp(line, "", 2))
	{
		perror("Error");
		free(line);
	}
}

void	process(char **cmd, char *line)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*pwd;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	char *envp[] = {pwd, NULL};
	if (!pid)
	{
		exec(cmd, envp, line);
	}
	else
		wait(NULL);
}

int main(int ac, char **av)
{
	char	*line;
	char	**command;

	(void)ac;
	(void)av;
	line = ft_strdup("");
	while (ft_strncmp(line, "exit", 5))
	{
		line = readline("Minaim> ");
		command = ft_split(line, ' ');
		add_history(line);
		if (!ft_strncmp(command[0], "pwd", 4))
			ft_printf("%s\n", getcwd(NULL, 0));
		else if (!ft_strncmp(command[0], "cd", 3))
			chdir(command[1]);
		else
			process(command, line);
	}		
	return 0;
}


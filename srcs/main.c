/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-07 16:26:03 by clouaint         ###   ########.fr       */
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

char	*get_command_path(char *command)
{
	char	**paths;
	char	*tmp_path;
	char	*full_path;
	int		i;
	char	*env_path;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp_path, command);
		free(tmp_path);
		if (access(full_path, X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_free(paths);
	return (NULL);
}

int	process(char **cmd, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (!ft_strncmp(cmd[0], "cd", 3))
		{
			chdir(cmd[1]);
			return (0);
		}
		else if (execve(get_command_path(cmd[0]), cmd, envp) == -1)
		{
			perror("Error");
			return (0);
		}
	}
	else
		wait(NULL);
	return (1);
}

int main(int argc, char **argv, char *envp[])
{
	char	*line;
	char	**cmd;

	(void)argv;
	if (argc > 1)
		return (-1);
	cmd = NULL;
	while (process(cmd, envp))
	{
		line = readline("Minishell> ");
		add_history(line);
		cmd = ft_split(line, ' ');
		if (!ft_strncmp(cmd[0], "exit", 5))
			return (0);
	}
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/08 16:27:31 by nferrad          ###   ########.fr       */
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

void	process(char **cmd, char *envp[], char *line)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (execve(get_command_path(cmd[0]), cmd, envp) == -1 && ft_strncmp(line, "exit", 5) && ft_strncmp(line, "", 2))
		{
			perror("Error");
			exit(0);
		}
	}
	else
		wait(NULL);
}

int main(int argc, char **argv, char *envp[])
{
	char	*line;
	char	**cmd;
	t_token	*token;

	(void)argv;
	if (argc > 1)
		return (-1);
sa	while (1)
	{
		line = readline("Minishell> ");
		add_history(line);
		parsing(line, t_token);
		if (!ft_strncmp(cmd[0], "cd", 3))yy
			chdir(cmd[1]);
		else
		{
			process(cmd, envp, line);
			if (!ft_strncmp(cmd[0], "exit", 5))
				return (0);
		}
	}
	return 0;
}

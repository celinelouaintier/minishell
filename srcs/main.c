/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/09 18:23:49 by nferrad          ###   ########.fr       */
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

void	process(t_token *cmd, char *env[])
{
	pid_t	pid;
	char	**args;
	t_token	*tmp;
	int		nb_arg;
	int		i;

	tmp = cmd;
	nb_arg = 0;
	while (tmp)
	{
		if (tmp->index == ARG)
			nb_arg++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * nb_arg + 1);
	if (!args)
		return ;
	i = 0;
	tmp = cmd;
	while (i < nb_arg + 1)
	{
		args[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	pid = fork();
	if (!pid)
	{
		if (execve(get_command_path(cmd->str), args, env) == -1 && ft_strncmp(cmd->str, "", 2))
		{
			perror("Error");
			exit(0);
		}
	}
	else
		wait(NULL);
}

int main(int argc, char **argv, char *env[])
{
	char	*line;
	t_token	*token;

	(void)argv;
	token = NULL;
	if (argc > 1)
		return (-1);
	while (1)
	{
		line = readline("Minishell> ");
		add_history(line);
		parsing(line, &token);
		// if (!ft_strncmp(, "cd", 3))
			// chdir(cmd[1]);
		// else
		// {
		process(token, env);
		if (!ft_strncmp(token->str, "exit", 5))
			return (0);
		// }
	}
	return 0;
}

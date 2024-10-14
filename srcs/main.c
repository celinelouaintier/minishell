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
	char	*path;

	tmp = cmd;
	nb_arg = 0;
	while (tmp)
	{
		if (tmp->index == ARG || tmp->index == CMD)
			nb_arg++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * nb_arg + 1);
	if (!args)
		return ;
	i = 0;
	tmp = cmd;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	pid = fork();
	if (!pid)
	{
		args[i] = NULL;
		path = get_command_path(cmd->str);
		if (!path)
		{
			perror("Error");
			exit(0);
		}
		if (execve(path, args, env) == -1 && ft_strncmp(cmd->str, "", 2))
		{
			perror("Error");
			exit(0);
		}
	}
	else
		wait(NULL);
}

void free_tokens(t_token **token)
{
    t_token *tmp;

    while (*token)
    {
        tmp = *token;
        *token = (*token)->next;
        free(tmp->str);
        free(tmp);
    }
}

int main(int argc, char **argv, char *env[])
{
	char	*line;
	t_token	*token;
	t_env	*envp;
	// char	*pwd;

	(void)argv;
	token = NULL;
	envp = malloc(sizeof(t_env));
	envp->PWD = malloc(PATH_MAX);
	getcwd(envp->PWD, PATH_MAX);
	if (argc > 1)
		return (-1);
	while (1)
	{
		line = readline("Minishell> ");
		add_history(line);
		free_tokens(&token);
		parsing(line, &token);
		if (token && !ft_strncmp(token->str, "exit", 5))
		{
			free_tokens(&token);
			return (0);
		}
		if (token && !ft_strncmp(token->str, "cd", 3))
			cd(token, envp);
		if (token && !ft_strncmp(token->str, "echo", 5))
			echo(token);
		else
			process(token, env);
		free_tokens(&token);
	}
}

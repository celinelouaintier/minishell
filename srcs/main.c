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

void	process(t_token *cmd, char *env[])
{
	pid_t	pid;
	char	*path;
	char	**args;

	pid = fork();
	if (!pid)
	{
		args = init_args(cmd);
		path = get_command_path(cmd->str);
		if (!path)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		if (execve(path, args, env) == -1 && ft_strncmp(cmd->str, "", 2))
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
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

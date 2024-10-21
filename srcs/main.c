/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/18 02:49:28 by nferrad          ###   ########.fr       */
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

void	signal_handler(int signum)
{
	if (signum == SIGSEGV)
	{
		ft_printf("Ferme Ta Gueule Celine !\n");
		exit(EXIT_FAILURE);
	}
	else if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("\nMinishell> ");
	}
}

int	main(int argc, char **argv, char *env[])
{
	char	*line;
	t_token	*token;
	t_env	*envp;

	(void)argv;
	token = NULL;
	envp = malloc(sizeof(t_env));
	envp->PWD = malloc(PATH_MAX);
	getcwd(envp->PWD, PATH_MAX);
	// signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	if (argc > 1)
		return (-1);
	while (1)
	{
		line = readline("Minishell> ");
		add_history(line);
		parsing(line, &token);
		if (is_builtin(token))
			exec_builtin(token, envp, env);
		else
			process_pipes(token, env);
		// if (token->index == CMD)
		//  	process(token, env);
		free_tokens(&token);
	}
}

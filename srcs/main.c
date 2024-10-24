/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/23 21:20:34 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGSEGV)
	{
		ft_printf("Ferme Ta Gueule Celine !\n");
		exit(EXIT_FAILURE);
	}
	else if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void set_sig()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
}

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->index == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

int	main(int argc, char **argv, char *env[])
{
	char				*line;
	t_token				*token;
	t_env				*envp;
	int					saved_stdout = -1;

	(void)argv;
	token = NULL;
	envp = malloc(sizeof(t_env));
	envp->pwd = malloc(PATH_MAX);
	getcwd(envp->pwd, PATH_MAX);
	if (argc > 1)
		return (-1);
	while (1)
	{
		set_sig();
		line = readline("Minishell> ");
		if (line && line[0] != '\0')
		{
			parsing(line, &token);
			if (token)
			{
				if (token && !ft_strncmp(token->str, "exit", 5) && token->index == CMD)
					ft_exit(token);
				add_history(line);
				handle_redirections(token, &saved_stdout);
				process_pipes(token, env, envp);
				restore_stdout(&saved_stdout);
				free_tokens(&token);
			}
		}
		else if (!line)
			ft_exit(token);
		free(line);
	}
}

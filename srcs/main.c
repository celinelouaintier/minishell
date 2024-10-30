/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/30 23:07:52 by nferrad          ###   ########.fr       */
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

void	set_sig(void)
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

t_exec	init_exec(t_token *token)
{
	t_exec	exec;

	exec.pipe_num = count_pipes(token);
	exec.pipe_fd = create_pipes(exec.pipe_num);
	exec.saved_stdout = -1;
	return (exec);
}

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->index == TRUNC || tmp->index == APPEND || tmp->index == INPUT
			|| tmp->index == HEREDOX || tmp->index == PIPE)
		{
			if (tmp->index == PIPE && !tmp->prev)
			{
				ft_printf(ERR_STX, tmp->str);
				return (0);
			}
			else if (!tmp->next || tmp->next->index == INPUT
					|| tmp->next->index == APPEND || tmp->next->index == TRUNC
					|| tmp->next->index == PIPE || tmp->next->index == HEREDOX)
			{
				if (tmp->next)
					ft_printf(ERR_STX, tmp->next->str);
				else
					ft_printf(ERR_NL);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv, char *env[])
{
	char				*line;
	t_token				*token;
	t_env				*envp;
	t_exec				exec;

	(void)argv;
	token = NULL;
	if (argc > 1)
		return (-1);
	envp = init_env(env);
	exec = init_exec(token);
	if (!envp)
	{
		ft_printf(ERR_ENV);
		return (-1);
	}
	while (1)
	{
		set_sig();
		line = readline("\001\033[0;34m\x1b[1m\002Minishell> \001\033[0m\002");
		if (line && line[0] != '\0')
		{
			parsing(line, &token, envp);
			if (token)
			{
				add_history(line);
				if (check_syntax(token))
				{
					if (is_builtin(token) && !has_pipe(token))
						exec_builtin(token, &envp, STDOUT_FILENO, &exec);
					else
						process_pipes(token, &envp);
					restore_stdout(&exec.saved_stdout);
				}
				free_tokens(&token);
			}
		}
		else if (!line)
			ft_exit(token);
		free(line);
	}
	// free_env(envp); // to be implemented
}

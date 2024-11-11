/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:26:03 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/08 03:01:25 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

t_exec	init_exec(t_token *token)
{
	t_exec	exec;

	exec.pipe_num = count_pipes(token);
	if (exec.pipe_num > 0)
		exec.pipe_fd = create_pipes(exec.pipe_num);
	else
		exec.pipe_fd = NULL;
	exec.saved_stdout = -1;
	exec.exit_status = 0;
	return (exec);
}

int	is_token_position_valid(t_token *token)
{
	if (token->index == PIPE && !token->prev)
	{
		ft_printf(ERR_STX, token->str);
		return (0);
	}
	else if (!token->next || token->next->index == INPUT
		|| token->next->index == APPEND || token->next->index == TRUNC
		|| token->next->index == PIPE || token->next->index == HEREDOX)
	{
		if (token->next)
			ft_printf(ERR_STX, token->next->str);
		else
			ft_printf(ERR_NL);
		return (0);
	}
	return (1);
}

int	check_syntax(t_env *envp, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->index == TRUNC || tmp->index == APPEND || tmp->index == INPUT
			|| tmp->index == HEREDOX || tmp->index == PIPE)
		{
			if (!is_token_position_valid(tmp))
			{
				update_exit_status(envp, 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void	do_exec(char *line, t_token *token, t_env *envp, t_exec *exec)
{
	while (1)
	{
		set_sig();
		line = readline("\001\033[0;34m\x1b[1m\002Minishell> \001\033[0m\002");
		if (g_sig)
		{
			update_exit_status(envp, g_sig + 128);
			g_sig = 0;
		}
		if (line && line[0] != '\0')
		{
			parsing(line, &token, envp);
			if (token)
			{
				add_history(line);
				if (check_syntax(envp, token))
				{
					if (is_builtin(token) && !has_pipe(token))
						exec_builtin(token, &envp, STDOUT_FILENO, exec);
					else
						process_pipes(token, &envp);
					restore_stdout(&exec->saved_stdout);
				}
				free_tokens(&token);
			}
		}
		else if (!line)
			ft_exit(token);
		free(line);
	}
}

int	main(int argc, char **argv, char *env[])
{
	char				*line;
	t_token				*token;
	t_env				*envp;
	t_exec				exec;

	(void)argv;
	if (argc > 1)
		return (-1);
	line = NULL;
	token = NULL;
	envp = init_env(env);
	exec = init_exec(token);
	if (!envp)
	{
		ft_printf(ERR_ENV);
		return (-1);
	}
	do_exec(line, token, envp, &exec);
}

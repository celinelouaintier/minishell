/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:37 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/18 14:32:56 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_token *token, t_env **env, int fd, t_exec *exec)
{
	int	error;

	error = 0;
	if (handle_redirections(token, exec) == -1)
	{
		error = 1;
		exec->exit_status = 1;
	}
	if (token && !ft_strncmp(token->str, "cd", 3))
		ft_cd(token, env);
	else if (token && !ft_strncmp(token->str, "echo", 5))
		echo(token, fd, error);
	else if (token && !ft_strncmp(token->str, "pwd", 4))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (token && !ft_strncmp(token->str, "export", 7))
		ft_export(token, env);
	else if (token && !ft_strncmp(token->str, "env", 4))
		print_env(*env);
	else if (token && !ft_strncmp(token->str, "unset", 6))
		ft_unset(token, env);
	else if (token && !ft_strncmp(token->str, "exit", 5))
		ft_exit(token, *env);
	update_exit_status(*env, exec->exit_status);
}

int	is_builtin(t_token *token)
{
	if (!ft_strncmp(token->str, "pwd", 4)
		|| !ft_strncmp(token->str, "cd", 3)
		|| !ft_strncmp(token->str, "echo", 5)
		|| !ft_strncmp(token->str, "exit", 5)
		|| !ft_strncmp(token->str, "env", 4)
		|| !ft_strncmp(token->str, "export", 7)
		|| !ft_strncmp(token->str, "unset", 6))
		return (1);
	else
		return (0);
}

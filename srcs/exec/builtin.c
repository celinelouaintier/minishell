/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:37 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/31 12:42:26 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_token *token, t_env **env, int fd, t_exec *exec)
{
	handle_redirections(token, exec);
	if (token && !ft_strncmp(token->str, "cd", 3) && token->index == CMD)
		ft_cd(token, env);
	else if (token && !ft_strncmp(token->str, "echo", 5) && token->index == CMD)
		echo(token, fd);
	else if (token && !ft_strncmp(token->str, "pwd", 4) && token->index == CMD)
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (token && !ft_strncmp(token->str, "export", 7) && token->index == CMD)
		ft_export(token, env);
	else if (token && !ft_strncmp(token->str, "env", 4) && token->index == CMD)
		print_env(*env);
	else if (token && !ft_strncmp(token->str, "unset", 6) && token->index == CMD)
		ft_unset(token, env);
	else if (token && !ft_strncmp(token->str, "exit", 5) && token->index == CMD)
		ft_exit(token);
}

int	is_builtin(t_token *token)
{
	if (token->index == CMD && (!ft_strncmp(token->str, "pwd", 4) ||
		!ft_strncmp(token->str, "cd", 3) || !ft_strncmp(token->str, "echo", 5) ||
		!ft_strncmp(token->str, "exit", 5) || !ft_strncmp(token->str, "env", 4) ||
		!ft_strncmp(token->str, "export", 7) || !ft_strncmp(token->str, "unset", 6)))
		return (1);
	else
		return (0);
}

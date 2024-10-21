/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 16:12:37 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-16 16:12:37 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_token *token, t_env *envp)
{
	if (token && !ft_strncmp(token->str, "exit", 5) && token->index == CMD)
		ft_exit(token);
	else if (token && !ft_strncmp(token->str, "cd", 3) && token->index == CMD)
		cd(token, envp);
	else if (token && !ft_strncmp(token->str, "echo", 5) && token->index == CMD)
		echo(token);
	else if (token && !ft_strncmp(token->str, "pwd", 4) && token->index == CMD)
		ft_printf("%s\n", getcwd(NULL, 0));
}

int	is_builtin(t_token *token)
{
	if (token->index == CMD && (!ft_strncmp(token->str, "pwd", 4) ||
		!ft_strncmp(token->str, "cd", 3) || !ft_strncmp(token->str, "echo", 5) ||
		!ft_strncmp(token->str, "exit", 5)))
		return (1);
	else
		return (0);
}
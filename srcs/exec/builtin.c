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
	{
		free_tokens(&token);
		exit(EXIT_SUCCESS);
	}
	else if (token && !ft_strncmp(token->str, "cd", 3) && token->index == CMD)
		cd(token, envp);
	else if (token && !ft_strncmp(token->str, "echo", 5) && token->index == CMD)
		echo(token);
}

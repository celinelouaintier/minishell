/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/02 12:41:51 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token *token, t_env **envp)
{
	t_env	*pwd;
	char	*current_pwd;

	if (!token->next || token->next->index != ARG)
	{
		chdir(getenv("HOME"));
		return ;
	}
	current_pwd = getcwd(NULL, 0);
	if (chdir(token->next->str) != 0)
	{
		perror("cd");
		free(current_pwd);
		return ;
	}
	pwd = *envp;
	while (pwd)
	{
		if (!ft_strncmp(pwd->name, "PWD", 4))
		{
			free(pwd->value);
			pwd->value = getcwd(NULL, 0);
			break ;
		}
		pwd = pwd->next;
	}
	pwd = *envp;
	while (pwd)
	{
		if (!ft_strncmp(pwd->name, "OLDPWD", 7))
		{
			free(pwd->value);
			pwd->value = current_pwd;
			break ;
		}
		pwd = pwd->next;
	}
}

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

void	change_dir(t_token *token)
{
	if (!token->next || token->next->index != ARG)
	{
		chdir(getenv("HOME"));
		return ;
	}
	if (chdir(token->next->str) != 0)
	{
		perror("cd");
		return ;
	}
}

void	update_pwd(t_env **envp, char *old_pwd)
{
	t_env	*pwd;

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
			pwd->value = ft_strdup(old_pwd);
			break ;
		}
		pwd = pwd->next;
	}
}

void	ft_cd(t_token *token, t_env **envp)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	change_dir(token);
	if (current_pwd)
		update_pwd(envp, current_pwd);
	free(current_pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/25 19:16:31 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	update_pwd(t_env **envp, char *name, char *new_value)
// {
// 	t_env	*tmp;
// 	t_env	*new;
	
// 	tmp = *envp;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->name, name, ft_strlen(name)) && tmp->name[ft_strlen(name)] == '\0')
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_strdup(new_value);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	new = add_env_var(name);
// 	new->value = ft_strdup(new_value);
// 	new->next = *envp;
// 	*envp = new;
// }

void	ft_cd(t_token *token, t_env **envp)
{
	t_env	*pwd;

	if (!token->next || token->next->index != ARG)
	{
		ft_printf("cd: missing argument\n");
		return ;
	}
	if (chdir(token->next->str) != 0)
		perror("cd");
	else
	{
		pwd = *envp;
		while (pwd)
		{
			if (!ft_strncmp(pwd->name, "PWD", 4))
			{
				free(pwd->value);
				pwd->value = getcwd(NULL, 0);
				ft_printf("%s\n", pwd->value);
				break ;
			}
			pwd = pwd->next;
		}
	}
}

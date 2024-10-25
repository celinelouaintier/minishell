/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:17:35 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/25 18:48:36 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_var(t_token *token, t_env **envp)
{
	char	*equal_sign;
	char	*env_var;
	t_env	*tmp;

	env_var = token->next->str;
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		tmp = *envp;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, env_var, equal_sign - env_var) && tmp->name[equal_sign - env_var] == '\0')
			{
				free(tmp->value);
				tmp->value = strdup(equal_sign + 1);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

void	ft_export(t_token *token, t_env **envp)
{
	t_env	*new;

	if (token->next && token->next->index == ARG)
	{
		ft_update_var(token, envp);
		new = add_env_var(token->next->str);
		if (!new)
		{
			perror("export");
			return ;
		}
		new->next = *envp;
		*envp = new;
	}
	else
		ft_printf("mettre env dans l'ordre\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:22:46 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/02 12:27:41 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env **env)
{
	t_env	*current;
	t_env	*sorted;
	t_env	*tmp;
	t_env	*next;

	sorted = NULL;
	current = *env;
	while (current)
	{
		next = current->next;
		if (!sorted || ft_strncmp(current->name, sorted->name,
				ft_strlen(current->name) + 1) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strncmp(current->name, tmp->next->name,
					ft_strlen(current->name) + 1) > 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = next;
	}
	*env = sorted;
}

void	ft_export(t_token *token, t_env **envp)
{
	t_env	*new;
	char	*env_var;

	if (token->next && token->next->index == ARG)
	{
		env_var = token->next->str;
		if (!check_name(env_var))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				env_var);
			return ;
		}
		if (!ft_update_var(token, envp))
		{
			new = add_env_var(env_var);
			if (!new)
			{
				perror("export");
				return ;
			}
			new->next = *envp;
			*envp = new;
		}
	}
	else
		print_export(*envp);
}

void	update_shlvl(t_env *env)
{
	t_env	*tmp;
	int		shlvl;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			shlvl = ft_atoi(tmp->value);
			free(tmp->value);
			shlvl++;
			tmp->value = ft_itoa(shlvl);
			return ;
		}
		tmp = tmp->next;
	}
}
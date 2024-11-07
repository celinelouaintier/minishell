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

void	insert_sorted_env(t_env **sorted, t_env *new_node)
{
	t_env	*tmp;

	if (!(*sorted) || ft_strncmp(new_node->name, (*sorted)->name,
			ft_strlen(new_node->name) + 1) < 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
	}
	else
	{
		tmp = *sorted;
		while (tmp->next && ft_strncmp(new_node->name, tmp->next->name,
				ft_strlen(new_node->name) + 1) > 0)
			tmp = tmp->next;
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
}

void	sort_env(t_env **env)
{
	t_env	*current;
	t_env	*sorted;
	t_env	*next;

	sorted = NULL;
	current = *env;
	while (current)
	{
		next = current->next;
		insert_sorted_env(&sorted, current);
		current = next;
	}
	*env = sorted;
}

void	ft_export(t_token *token, t_env **envp)
{
	t_env	*new;

	if (!token->next || token->next->index != ARG)
		print_export(*envp);
	while (token->next && token->next->index == ARG)
	{
		if (!check_name(token->next->str))
		{
			ft_printf("`%s' not a valid identifier\n", token->next->str);
			token = token->next;
			continue ;
		}
		if (!ft_update_var(token, envp))
		{
			new = add_env_var(token->next->str);
			if (!new)
			{
				perror("export");
				return ;
			}
			new->next = *envp;
			*envp = new;
		}
		token = token->next;
	}
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

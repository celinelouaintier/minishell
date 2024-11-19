/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:22:46 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/18 14:42:28 by clouaint         ###   ########.fr       */
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

t_env	*find_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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

int	check_name(char *name)
{
	int	i;

	i = 0;
	if (!name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
	{
		ft_printf("`%s' not a valid identifier\n", name);
		return (0);
	}
	i++;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_printf("`%s' not a valid identifier\n", name);
			return (0);
		}
		i++;
	}
	return (1);
}

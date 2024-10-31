/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:17:35 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/31 11:01:21 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_var(t_token *token, t_env **envp)
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
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

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
		if (!sorted || ft_strncmp(current->name, sorted->name, ft_strlen(current->name) + 1) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strncmp(current->name, tmp->next->name, ft_strlen(current->name) + 1) > 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = next;
	}
	*env = sorted;
}

void	print_export(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	sort_env(&tmp);
	while (tmp)
	{
		if(tmp->value[0] != '"' || tmp->value[ft_strlen(tmp->value) - 1] != '"')
			ft_printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		else
			ft_printf("export %s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

int	check_name(char *name)
{
	int	i;

	i = 0;
	if (!name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
			ft_printf("minishell: export: `%s': not a valid identifier\n", env_var);
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

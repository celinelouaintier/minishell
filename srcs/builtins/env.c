/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:51:49 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/25 18:37:33 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		else
			ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}


void	update_parent_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)) && tmp->name[ft_strlen(name)] == '\0')
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = add_env_var(name);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

t_env	*add_env_var(char *env_var)
{
	t_env	*new;
	char	*equal_sign;
	size_t	name_len;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		name_len = equal_sign - env_var;
		new->name = ft_substr(env_var, 0, name_len);
		if (!new->name)
		{
			free(new);
			exit(EXIT_FAILURE);
		}
		new->value = strdup(equal_sign + 1);
		if (!new->value)
		{
			free(new->name);
			free(new);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new->value = NULL;
		new->name = strdup(env_var);
	}
	new->next = NULL;
	return (new);
}

t_env	*sync_env(t_env *child_env)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = NULL;
	tmp = child_env;
	while (tmp)
	{
		update_parent_env(&new_env, tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (new_env);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*new;
	int		i;

	head = NULL;
	tmp = NULL;
	i = 0;
	while (env[i])
	{
		new = add_env_var(env[i]);
		if (!head)
		{
			head = new;
			tmp = head;
		}
		else
		{
			tmp->next = new;
			tmp = new;
		}
		i++;
	}
	return (head);
}

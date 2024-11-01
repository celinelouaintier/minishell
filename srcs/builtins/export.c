/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:17:35 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/01 23:15:50 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env_list(t_env *env) 
{
    t_env *new_list;
    t_env *new_node;
    t_env *tmp = env;

	new_list = NULL;
    while (tmp) {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            exit(EXIT_FAILURE);
        new_node->name = ft_strdup(tmp->name);
        new_node->value = tmp->value ? strdup(tmp->value) : NULL;
        new_node->next = new_list;
        new_list = new_node;
        tmp = tmp->next;
    }
    return new_list;
}

int	ft_update_var(t_token *token, t_env **envp)
{
	char	*equal_sign;
	char	*env_var;
	t_env	*tmp;
	int		quote;

	env_var = token->next->str;
	equal_sign = ft_strchr(env_var, '=');
	quote = 0;
	if (equal_sign && (equal_sign[1] == '\'' || equal_sign[1] == '\"'))
	{
		if (!check_quote(equal_sign, 2, equal_sign[1]))
			return (-1);
		quote++;
	}
	if (equal_sign)
	{
		tmp = *envp;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, env_var, equal_sign - env_var) && tmp->name[equal_sign - env_var] == '\0')
			{
				free(tmp->value);
				if (quote)
					tmp->value = ft_substr(equal_sign, 2, ft_strlen(equal_sign) - 3);
				else
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

void print_export(t_env *envp) {
    t_env *copy;
    t_env *tmp;

	copy = copy_env_list(envp);
    sort_env(&copy);
	tmp = copy;
    while (tmp) {
        if (tmp->value)
            ft_printf("export %s=\"%s\"\n", tmp->name, tmp->value);
        else
            ft_printf("export %s\n", tmp->name);
        tmp = tmp->next;
    }
    tmp = copy;
    while (tmp) {
        free(tmp->name);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
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

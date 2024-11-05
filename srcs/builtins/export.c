/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:17:35 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/02 12:31:33 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env_list(t_env *env)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*tmp;

	tmp = env;
	new_list = NULL;
	while (tmp)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			exit(EXIT_FAILURE);
		new_node->name = ft_strdup(tmp->name);
		if (tmp->value)
			new_node->value = strdup(tmp->value);
		else
			new_node->value = NULL;
		new_node->next = new_list;
		new_list = new_node;
		tmp = tmp->next;
	}
	return (new_list);
}

int	update_env_value(t_env *env_var_node, char *equal_sign, int quote)
{
	free(env_var_node->value);
	if (quote)
		env_var_node->value = ft_substr(equal_sign, 2,
				ft_strlen(equal_sign) - 3);
	else
		env_var_node->value = strdup(equal_sign + 1);
	return (1);
}

int	ft_update_var(t_token *token, t_env **envp)
{
	char	*equal_sign;
	t_env	*tmp;
	int		quote;

	equal_sign = ft_strchr(token->next->str, '=');
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
			if (!ft_strncmp(tmp->name, token->next->str,
					equal_sign - token->next->str)
				&& tmp->name[equal_sign - token->next->str] == '\0')
				return (update_env_value(tmp, equal_sign, quote));
			tmp = tmp->next;
		}
	}
	return (0);
}

void	print_export(t_env *envp)
{
	t_env	*copy;
	t_env	*tmp;

	copy = copy_env_list(envp);
	sort_env(&copy);
	tmp = copy;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		else
			ft_printf("export %s\n", tmp->name);
		tmp = tmp->next;
	}
	tmp = copy;
	while (tmp)
	{
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

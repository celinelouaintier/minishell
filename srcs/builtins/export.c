/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:17:35 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/08 02:52:12 by nferrad          ###   ########.fr       */
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

	equal_sign = ft_strchr(token->str, '=');
	quote = 0;
	if (equal_sign && (equal_sign[1] == '\'' || equal_sign[1] == '\"'))
	{
		if (!check_quote(equal_sign, 2, equal_sign[1], *envp))
			return (-1);
		quote++;
	}
	if (equal_sign)
	{
		tmp = *envp;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, token->str,
					equal_sign - token->str)
				&& tmp->name[equal_sign - token->str] == '\0')
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
		if (ft_strncmp(tmp->name, "?", 2))
		{
			if (tmp->value)
				ft_printf("export %s=\"%s\"\n", tmp->name, tmp->value);
			else
				ft_printf("export %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	tmp = copy;
	free_env(copy);
}

void	ft_export(t_token *token, t_env **envp)
{
	t_env	*new;

	if (!token->next || token->next->index != ARG)
		print_export(*envp);
	while (token->next && token->next->index == ARG)
	{
		token = token->next;
		if (!check_name(token->str))
			continue ;
		if (!ft_update_var(token, envp))
		{
			if (!ft_strchr(token->str, '=') && find_env_var(*envp,
					token->str))
				continue ;
			new = add_env_var(token->str);
			if (!new)
			{
				perror("export");
				return ;
			}
			new->next = *envp;
			*envp = new;
		}
	}
}

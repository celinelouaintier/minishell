/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:51:49 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/01 01:16:56 by nferrad          ###   ########.fr       */
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

t_env	*add_env_var(char *env_var)
{
	t_env	*new;
	char	*equal_sign;
	size_t	name_len;
	int		quote;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	equal_sign = ft_strchr(env_var, '=');
	quote = 0;
	if (equal_sign && (equal_sign[1] == '\'' || equal_sign[1] == '\"'))
	{
		if (!check_quote(equal_sign, 2, equal_sign[1]))
			exit(-1);
		quote++;
	}
	if (equal_sign)
	{
		name_len = equal_sign - env_var;
		new->name = ft_substr(env_var, 0, name_len);
		if (!new->name)
		{
			free(new);
			exit(EXIT_FAILURE);
		}
		if (quote)
			new->value = ft_substr(equal_sign, 2, ft_strlen(equal_sign) - 3);
		else
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

void	ft_unset(t_token *token, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	char	*name;

	tmp = *env;
	name = token->next->str;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	ft_printf("minishell: unset: `%s': not a valid identifier\n", name);
}

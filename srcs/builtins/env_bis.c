/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 12:57:52 by clouaint          #+#    #+#             */
/*   Updated: 2024-11-05 12:57:52 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env_name(t_env *new, char *env_var, char *equal_sign)
{
	size_t	name_len;

	if (equal_sign)
	{
		name_len = equal_sign - env_var;
		new->name = ft_substr(env_var, 0, name_len);
		if (!new->name)
			return (0);
	}
	else
	{
		new->name = strdup(env_var);
		if (!new->name)
			return (0);
	}
	return (1);
}

int	set_env_value(t_env *new, char *equal_sign)
{
	int	quote;

	quote = 0;
	if (equal_sign && (equal_sign[1] == '\'' || equal_sign[1] == '\"'))
		quote++;
	if (equal_sign)
	{
		if (quote)
			new->value = ft_substr(equal_sign, 2, ft_strlen(equal_sign) - 3);
		else
			new->value = strdup(equal_sign + 1);
		if (!new->value)
			return (0);
	}
	else
		new->value = NULL;
	return (1);
}

t_env	*init_env_var(t_env *new, char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (!set_env_name(new, env_var, equal_sign))
	{
		free_env_var(new);
		exit(EXIT_FAILURE);
	}
	if (!set_env_value(new, equal_sign))
	{
		free_env_var(new);
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	return (new);
}

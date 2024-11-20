/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:21:02 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/20 12:50:45 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	if (token && *token)
	{
		while (*token)
		{
			tmp = *token;
			*token = (*token)->next;
			if (tmp->str)
				free(tmp->str);
			free(tmp);
		}
		*token = NULL;
	}
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_env_var(t_env *env_var)
{
	if (env_var)
	{
		free(env_var->name);
		free(env_var->value);
		free(env_var);
	}
}

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->index == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	free_env(t_env *envp)
{
	t_env	*tmp;

	while (envp)
	{
		tmp = envp->next;
		free(envp->name);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = tmp;
	}
}

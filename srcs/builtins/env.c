/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:51:49 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/15 22:39:08 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "?", 2))
		{
			if (tmp->value)
				ft_printf("%s=%s\n", tmp->name, tmp->value);
			else if (!ft_strncmp(tmp->name, "=", 1))
				ft_printf("%s\n", tmp->name);
		}
		tmp = tmp->next;
	}
}

t_env	*add_env_var(char *env_var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new = init_env_var(new, env_var);
	return (new);
}

t_env	*set_exit_status(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	new->name = ft_strdup("?");
	if (!new->name)
		exit(EXIT_FAILURE);
	new->value = ft_strdup("0");
	if (!new->value)
		exit(EXIT_FAILURE);
	return (new);
}

void	finalize_env(t_env *head, t_env *tmp)
{
	t_env	*new;

	new = set_exit_status();
	tmp->next = new;
	update_shlvl(head);
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
	finalize_env(head, tmp);
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:54:43 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/16 14:07:30 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, int fd, int error)
{
	int		skip_line;
	t_token	*tmp;

	if (error)
		return ;
	tmp = token->next;
	skip_line = 0;
	while (tmp != NULL && !ft_strncmp(tmp->str, "-n", 3) && tmp->index == ARG)
	{
		skip_line = 1;
		tmp = tmp->next;
	}
	while (tmp != NULL && tmp->index == ARG)
	{
		ft_putstr_fd(tmp->str, fd);
		tmp = tmp->next;
		if (tmp != NULL && tmp->index == ARG)
			ft_putstr_fd(" ", fd);
	}
	if (!skip_line)
		ft_putstr_fd("\n", fd);
}

void	check_unset_error(t_token *t, t_env *tmp)
{
	if (!tmp)
		ft_printf("unset: `%s': not a valid identifier\n", t->str);
}

void	ft_unset(t_token *t, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	t = t->next;
	while (t)
	{
		tmp = *env;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, t->str, ft_strlen(t->str) + 1))
			{
				if (prev)
					prev->next = tmp->next;
				else
					*env = tmp->next;
				free_env_var(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		check_unset_error(t, tmp);
		t = t->next;
	}
}

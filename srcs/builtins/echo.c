/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:54:43 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/18 02:51:27 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token)
{
	int		skip_line;
	t_token	*tmp;

	tmp = token->next;
	skip_line = 0;
	if (tmp != NULL &&!ft_strncmp(tmp->str, "-n", 3) && tmp->index == ARG)
	{
		skip_line = 1;
		tmp = tmp->next;
	}
	while (tmp != NULL && tmp->index == ARG)
	{
		ft_putstr_fd(tmp->str, STDOUT_FILENO);
		tmp = tmp->next;
		if (tmp != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!skip_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

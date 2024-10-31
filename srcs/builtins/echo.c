/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:54:43 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/01 00:47:35 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, int fd)
{
	int		skip_line;
	t_token	*tmp;

	tmp = token->next;
	skip_line = 0;
	while (tmp != NULL &&!ft_strncmp(tmp->str, "-n", 3) && tmp->index == ARG)
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

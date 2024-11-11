/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 05:46:17 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/11 17:59:14 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_check(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

int	check_quote(char *line, int i, char quote, t_env *envp)
{
	while (line[i])
	{
		if (line[i] == quote)
			return (1);
		i++;
	}
	ft_printf(ERR_QUOTE, quote);
	update_exit_status(envp, 2);
	return (0);
}

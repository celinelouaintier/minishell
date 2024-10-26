/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 05:46:17 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/26 05:55:57 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command(char *line, int *i, t_token **token)
{
	int	j;

	j = *i;
	while (line[*i] && end_check(line[*i]))
		(*i)++;
	lstadd_back(token, lstnew(ft_substr(line, j, *i - j), CMD));
}

int	end_check(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

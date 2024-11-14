/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 05:46:17 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/14 02:13:41 by nferrad          ###   ########.fr       */
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

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->index == CMD)
			ft_printf("CMD	");
		else if (token->index == ARG)
			ft_printf("ARG	");
		else if (token->index == PIPE)
			ft_printf("PIPE	");
		else if (token->index == HEREDOX)
			ft_printf("HEREDOX	");
		else if (token->index == APPEND)
			ft_printf("APPEND	");
		else if (token->index == INPUT)
			ft_printf("INPUT	");
		else if (token->index == TRUNC)
			ft_printf("TRUNC	");
		else
			ft_printf("%d	", token->index);
		ft_printf("/////	%s\n", token->str);
		token = token->next;
	}
}

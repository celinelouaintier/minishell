/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:52:11 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/22 18:01:50 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token *token)
{
	int		i;
	char	*str;
	int		exit_code;

	if (token && token->next)
	{
		i = 0;
		str = token->next->str;
		if (str[i] == '+' || str[i] == '-')
			i++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		ft_printf("exit\n");
		if (str[i])
		{
			ft_printf("exit: %s: numeric argument required\n", token->next->str);
			exit(2);
		}
		if (token->next->next)
		{
			ft_printf("exit: too many arguments\n");
			return ;
		}
		exit_code = ft_atoi(str);
		exit(exit_code);
	}
	else
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

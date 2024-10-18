/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 12:52:11 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-18 12:52:11 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

void	ft_exit(t_token *token)
{
	int		i;
	char	*str;
	int		exit_code;

	if (token->next)
	{
		i = 0;
		str = token->next->str;
		if (str[i] == '+' || str[i] == '-')
			i++;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
			{
				ft_printf("exit: %s: numeric argument required\n", token->next->str);
				return ;
			}
			i++;
		}
		if (token->next->next)
		{
			ft_printf("exit: too many arguments\n");
			return ;
		}
		exit_code = ft_atoi(str);
		ft_printf("exit\n");
		exit(exit_code);
	}
	else
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

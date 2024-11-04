/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:52:11 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/02 12:42:24 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_arg(t_token *token, char *str)
{
	int		i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	ft_printf("exit\n");
	if (str[i])
	{
		ft_printf("exit: %s: numeric argument required\n",
			token->next->str);
		exit(2);
	}
	if (token->next->next)
	{
		ft_printf("exit: too many arguments\n");
		return (0);
	}
	return (1);
}

void	ft_exit(t_token *token)
{
	char	*str;
	int		exit_code;

	if (token && token->next)
	{
		str = token->next->str;
		if (check_exit_arg(token, str))
		{
			exit_code = ft_atoi(str);
			exit(exit_code);
		}
	}
	else
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

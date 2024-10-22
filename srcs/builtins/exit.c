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
		if (str[i])
			return (void)ft_printf("exit: %s: numeric argument required\n", token->next->str);
		if (token->next->next)
			return (void)ft_printf("exit: too many arguments\n");
		exit_code = ft_atoi(str);
		ft_printf("exit\n");
		exit(exit_code);
	}
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}

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
	if (token->next)
	{
		char *str = token->next->str;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] < '0' || str[i] > '9')
			{
				ft_printf("exit: %s: numeric argument required\n", token->next->str);
				return ;
			}
		}
		int exit_code = ft_atoi(str);
		exit(exit_code);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}
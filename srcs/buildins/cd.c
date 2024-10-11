/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-11 12:49:18 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_token *token, t_env *envp)
{
	// if (!path)
		// chdir($HOME);
	chdir(token->next->str);
	getcwd(envp->PWD, INT_MAX);
	ft_printf("%s\n", envp->PWD);
}
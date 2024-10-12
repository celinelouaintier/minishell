/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/12 20:10:35 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_token *token, t_env *envp)
{
	// if (!path)
		// chdir($HOME);
	if (token->next != NULL && token->next->index == ARG)
		chdir(token->next->str);
	else
		chdir("/home/");
	getcwd(envp->PWD, PATH_MAX);
	// ft_printf("%s\n", envp->PWD);
}

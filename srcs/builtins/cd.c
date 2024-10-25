/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:44 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_token *token)
{
	char	*path;

	path = NULL;
	if (token->next != NULL && token->next->index == ARG)
		path = token->next->str;
	else
		path = "/home/";
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
	// if (getcwd(envp->pwd, PATH_MAX) == NULL)
	// 	perror("getcwd");
}

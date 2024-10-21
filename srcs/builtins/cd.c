/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:18 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/18 02:51:10 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_token *token, t_env *envp)
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
	if (getcwd(envp->PWD, PATH_MAX) == NULL)
		perror("getcwd");
}
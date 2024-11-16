/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:46:52 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/16 15:44:00 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew(char *content, int index)
{
	t_token	*element;

	if (!content)
		return (NULL);
	element = malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->index = index;
	element->str = content;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

t_token	*lstlast(t_token *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	lstadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		lstlast(*lst)->next = new;
		new->prev = lstlast(*lst);
	}
	else
		*lst = new;
}

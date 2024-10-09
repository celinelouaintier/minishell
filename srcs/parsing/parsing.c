/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/09 17:26:10 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew(char *content, int index)
{
	t_token	*element;

	element = malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->index = index;
	element->str = content;
	element->next = NULL;
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
		lstlast(*lst)->next = new;
	else
		*lst = new;
}

// TODO :	Corriger les >> & <<
//			Séparer > >> << < en 4 conditions distincts
//			Revoir Heredoc (demander a la vielle)
//			Flag ?

void	parsing(char *line, t_token **token)
{
	int		i;
	int		j;
	int		index;
	int		next_index;

	i = 0;
	next_index = CMD;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		j = i;
		if (next_index == CMD)
		{
			index = CMD;
			next_index = 0;
		}
		else if (next_index == FILE)
		{
			index = FILE;
			next_index = 0;
		}
		else if (!next_index)
		{
			next_index = FILE;
			if (line[i] == '|')
			{
				index = PIPE;
				next_index = CMD;
			}
			else if (line[i] == '<' || line[i] == '>')
				index = 4;
			else if (!ft_strncmp(line, ">>", 3) || !ft_strncmp(line, "<<", 3))
				index = 5;
			else
			{
				index = ARG;
				next_index = 0;
			}
		}
		if (index == CMD || index == ARG || index == FILE)
			while(ft_isalpha(line[j]))
				j++;
		else if (index == PIPE || index == 4)
			j++;
		else if (index == 5)
			j += 2;
		lstadd_back(token, lstnew(ft_substr(line, i, j - i), index)); // Code de Celine //
		i = j;
	}
	// while (token)
	// {
	// 	if (token->index == CMD)
	// 		ft_printf("CMD	");
	// 	else if (token->index == ARG)
	// 		ft_printf("ARG	");
	// 	else if (token->index == PIPE)
	// 		ft_printf("PIPE	");
	// 	else if (token->index == FILE)
	// 		ft_printf("FILE	");
	// 	else
	// 		ft_printf("%d	", token->index);
	// 	ft_printf("/////	%s\n", token->str);
	// 	token = token->next;	
	// }
}
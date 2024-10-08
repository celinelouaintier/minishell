/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/08 19:48:31 by nferrad          ###   ########.fr       */
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

void	parsing(char *line, t_token *token)
{
	int		i;
	int		j;
	int		index;
	int		next_index;

	i = 0;
	next_index = 0;
	index = CMD;
	while (line[i] == ' ')
		i++;
	j = i;
	while(ft_isalpha(line[j]))
		j++;
	lstadd_back(&token, lstnew(ft_substr(line, i, j - i), index));
	i = j;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (next_index == CMD)
			index = CMD;
		else if (lstlast(token)->index == CMD || lstlast(token)->index == ARG)
		{
			next_index = CMD;
			if (line[i] == '|')
				index = PIPE;
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
		j = i;
		if (index == CMD || index == ARG)
			while(ft_isalpha(line[j]))
				j++;
		else if (index == PIPE || index == 4)
			j++;
		else if (index == 5)
			j += 2;
		lstadd_back(&token, lstnew(ft_substr(line, i, j - i), index)); // Code de Celine //
		i = j;		
	}
	while (token)
	{
		if (token->index == CMD)
			ft_printf("CMD	");
		else if (token->index == ARG)
			ft_printf("ARG	");
		else if (token->index == PIPE)
			ft_printf("PIPE	");
		ft_printf("/////	%s\n", token->str);
		token = token->next;	
	}
}

int	main(int argc, char **argv)
{
	t_token *token = NULL;
	parsing(argv[argc - 1], token);
	return (0);
}
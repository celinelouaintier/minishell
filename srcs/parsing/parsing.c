/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/14 03:21:31 by nferrad          ###   ########.fr       */
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

int	check(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (0);
	return (1);
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
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		j = i;
		if (next_index == CMD)
		{
			index = CMD;
			next_index = 0;
		}
		else if (!next_index)
		{
			if (line[i] == '|')
			{
				index = PIPE;
				next_index = CMD;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
				index = APPEND;
			else if (line[i] == '<' && line[i + 1] == '<')
				index = HEREDOX;
			else if (line[i] == '>')
				index = TRUNC;
			else if (line[i] == '<')
				index = INPUT;
			else
				index = ARG;
		}
		if (index == CMD || index == ARG)
			while(line[j] && check(line[j]))
				j++;
		else if (index == PIPE || index == TRUNC || index == INPUT)
			j++;
		else if (index == HEREDOX || index == APPEND)
			j += 2;
		lstadd_back(token, lstnew(ft_substr(line, i, j - i), index)); // Code de Celine //
		i = j;
		while (line[i] == ' ')
			i++;
	}
	// while ((*token))
	// {
	// 	if ((*token)->index == CMD)
	// 		ft_printf("CMD	");
	// 	else if ((*token)->index == ARG)
	// 		ft_printf("ARG	");
	// 	else if ((*token)->index == PIPE)
	// 		ft_printf("PIPE	");
	// 	else if ((*token)->index == HEREDOX)
	// 		ft_printf("HEREDOX	");
	// 	else if ((*token)->index == APPEND)
	// 		ft_printf("APPEND	");
	// 	else if ((*token)->index == INPUT)
	// 		ft_printf("INPUT	");
	// 	else if ((*token)->index == TRUNC)
	// 		ft_printf("TRUNC	");
	// 	else
	// 		ft_printf("%d	", (*token)->index);
	// 	ft_printf("/////	%s\n", (*token)->str);
	// 	(*token) =(*token)->next;	
	// }
}

// int	main(int argc, char **argv)
// {
// 	t_token *token;
// 	token = NULL;
// 	parsing(argv[argc - 1], &token);
// 	return (0);
// }
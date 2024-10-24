/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/24 14:03:26 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->index == CMD)
			ft_printf("CMD	");
		else if (token->index == ARG)
			ft_printf("ARG	");
		else if (token->index == PIPE)
			ft_printf("PIPE	");
		else if (token->index == HEREDOX)
			ft_printf("HEREDOX	");
		else if (token->index == APPEND)
			ft_printf("APPEND	");
		else if (token->index == INPUT)
			ft_printf("INPUT	");
		else if (token->index == TRUNC)
			ft_printf("TRUNC	");
		else
			ft_printf("%d	", token->index);
		ft_printf("/////	%s\n", token->str);
		token = token->next;	
	}
}
/*
int	set_index(int index, int *next_index, char c, char d)
{
	if (*next_index == CMD)
	{
		index = CMD;
		*next_index = 0;
	}
	else if (!*next_index)
	{
		if (c == '|')
		{
			index = PIPE;
			*next_index = CMD;
		}
		else if (c == '>' && d == '>')
			index = APPEND;
		else if (c == '<' && d == '<')
			index = HEREDOX;
		else if (c == '>')
			index = TRUNC;
		else if (c == '<')
			index = INPUT;
		else
			index = ARG;
	}
	return (index);
}

// TODO :	Revoir Heredoc (demander a la vielle)

void	parsing(char *line, t_token **token)
{
	int		i;
	int		j;
	int		index;
	int		next_index;

	i = 0;
	next_index = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		j = i;
		index = set_index(index, &next_index, line[i], line[i + 1]);
		if (index == CMD || index == ARG)
			while (line[j] && check(line[j]))
				j++;
		else if (index == PIPE || index == TRUNC || index == INPUT)
			j++;
		else if (index == HEREDOX || index == APPEND)
			j += 2;
		lstadd_back(token, lstnew(ft_substr(line, i, j - i), index));
		i = j;
		while (line[i] == ' ')
			i++;
	}
	print_token(*token);
}
*/

int	check(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

void	parsing(char *line, t_token **token)
{
	int	i;
	int	j;
	int	index;
	int	next;
	int	quote;

	i = 0;
	next = CMD;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		j = i;
		quote = 0;
		if (line[i] == '<' && line[i + 1] == '<')
		{
			next = ARG;
			index = HEREDOX;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			next = ARG;
			index = APPEND;
		}
		else if (line[i] == '>')
		{
			next = ARG;
			index = TRUNC;
		}
		else if (line[i] == '<')
		{
			next = ARG;
			index = INPUT;
		}
		else if (line[i] == '|')
		{
			next = CMD;
			index = PIPE;
		}
		else if (next == CMD)
		{
			next = ARG;
			index = CMD;
		}
		else 
		{
			index = ARG;
			if (line[i] == '\'' || line[i] == '\"')
			{
				j++;
				while (line[i] != line[j] && line[j])
					j++;
				i++;
				quote = 1;
			}
		}
		if (index == CMD || (index == ARG && !quote))
			while (line[j] && check(line[j]))
				j++;
		else if (index == PIPE || index == TRUNC || index == INPUT)
			j++;
		else if (index == HEREDOX || index == APPEND)
			j += 2;
		lstadd_back(token, lstnew(ft_substr(line, i, j - i), index));
		i = j;
		if (quote)
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
	// print_token(*token);
}

// int	main(int argc, char **argv)
// {
// 	t_token *token;
// 	token = NULL;
// 	parsing(argv[argc - 1], &token);
// 	return (0);
// }

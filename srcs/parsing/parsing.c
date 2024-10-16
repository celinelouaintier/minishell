/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/14 03:46:30 by nferrad          ###   ########.fr       */
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

int	check(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

// TODO :	Revoir Heredoc (demander a la vielle)

void	parsing(char *line, t_token **token)
{
	int		i;
	int		j;
	int		index = 0;
	int		next_index;

	i = 0;
	next_index = CMD;
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
	// print_token(*token);
}

// int	main(int argc, char **argv)
// {
// 	t_token *token;
// 	token = NULL;
// 	parsing(argv[argc - 1], &token);
// 	return (0);
// }

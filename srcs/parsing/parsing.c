/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/16 16:07:04 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strarg(char *line, int *i, t_env *env)
{
	char	quote;
	char	*arg;

	quote = 0;
	arg = NULL;
	while (line[*i])
	{
		if (!last_quote(&quote, line, i) || (!quote && !end_check(line[*i])))
			break ;
		if (!quote && (line[*i] == '\'' || line[*i] == '\"'))
		{
			quote = line[*i];
			(*i)++;
			if (empty_quote(i, line, quote, &arg))
				break ;
			if (!check_quote(line, *i, quote, env))
				return (NULL);
		}
		if (line[*i] == '$' && quote != '\'')
			arg = set_arg(arg, line, i, env);
		else
			arg = addback(arg, line[*i]);
		(*i)++;
	}
	return (arg);
}

int	set_index3(int *cmd, char *line, int *i, t_token **token)
{
	if (line[*i] == '|')
	{
		(*cmd) = 1;
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), PIPE));
		return (1);
	}
	return (0);
}

int	set_index2(int *cmd, char *line, int *i, t_token **token)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*cmd) = 0;
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), HEREDOX));
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*cmd) = 0;
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), APPEND));
	}
	else if (line[*i] == '>')
	{
		(*cmd) = 0;
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), TRUNC));
	}
	else if (line[*i] == '<')
	{
		(*cmd) = 0;
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), INPUT));
	}
	else
		return (0);
	return (1);
}

int	set_index(char *line, int *i, t_env *env, t_token **token)
{
	char		*arg;
	static int	cmd = 0;

	if (!set_index2(&cmd, line, i, token) && !set_index3(&cmd, line, i, token))
	{
		arg = strarg(line, i, env);
		if (!arg)
			return (0);
		if (cmd || !(*token))
		{
			lstadd_back(token, lstnew(arg, CMD));
			cmd = 0;
		}
		else
		{
			if (lstlast(*token)->index == HEREDOX
				|| lstlast(*token)->index == APPEND
				|| lstlast(*token)->index == TRUNC
				|| lstlast(*token)->index == INPUT)
				cmd = 1;
			lstadd_back(token, lstnew(arg, ARG));
		}
	}
	return (1);
}

void	parsing(char *line, t_token **token, t_env *env)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (!set_index(line, &i, env, token))
		{
			add_history(line);
			free_tokens(token);
			return ;
		}
		if (lstlast(*token)->index == HEREDOX
			|| lstlast(*token)->index == APPEND)
			i += 2;
		else if (lstlast(*token)->index == PIPE
			|| lstlast(*token)->index == TRUNC
			|| lstlast(*token)->index == INPUT)
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
	print_token(*token);
}

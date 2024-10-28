/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/10/28 22:58:05 by nferrad          ###   ########.fr       */
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

char	*set_arg(char *arg, char *line, int *i, char *env[])
{
	int		k;
	int		j;
	char	*env_var;

	j = *i + 1;
	while (line[j] && end_check(line[j]) && line[j] != '\'' && line[j] != '\"')
		j++;
	j -= *i;
	env_var = ft_substr(line, *i + 1, j - 1);
	k = 0;
	while (env[k])
	{
		if (!ft_strncmp(env[k], env_var, j - 1))
		{
			arg = ft_strjoin(arg, ft_substr(env[k], j, ft_strlen(env[k]) - j));
			break ;
		}
		k++;
	}
	(*i) += j - 1;
	return (arg);
}

char	*strarg(char *line, int *i, char *env[])
{
	char	quote;
	char	*arg;

	quote = 0;
	arg = ft_strdup("");
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		(*i)++;
	}
	while (line[*i] && (end_check(line[*i]) || quote != 0))
	{
		if (line[*i] == '$' && quote != '\'')
			arg = set_arg(arg, line, i, env);
		else
			arg = ft_strjoin(arg, ft_substr(line, *i, 1));
		(*i)++;
		if (line[*i] == quote)
		{
			(*i)++;
			break ;
		}
	}
	return (arg);
}

void	set_index(char *line, int *i, char *env[], t_token **token)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), HEREDOX));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), APPEND));
	else if (line[*i] == '>')
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), TRUNC));
	else if (line[*i] == '<')
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), INPUT));
	else if (line[*i] == '|')
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), PIPE));
	else if (!*token || lstlast(*token)->index == PIPE)
		add_command(line, i, token);
	else
		lstadd_back(token, lstnew(strarg(line, i, env), ARG));
}

void	parsing(char *line, t_token **token, char *env[])
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		set_index(line, &i, env, token);
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
	// print_token(*token);
}

/*

>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<
Decommente ici stv l'ancien parsing
>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<

void	parsing(char *line, t_token **token, char *env[])
{
	int	i;
	int	j;
	int	index;
	int	next;

	i = 0;
	next = CMD;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		j = i;
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
			lstadd_back(token, lstnew(strarg(line, &i, env), ARG));
		}
		if (index == CMD)
			while (line[j] && check(line[j]))
				j++;
		else if (index == PIPE || index == TRUNC || index == INPUT)
			j++;
		else if (index == HEREDOX || index == APPEND)
			j += 2;
		if (index != ARG)
		{
			lstadd_back(token, lstnew(ft_substr(line, i, j - i), index));
			i = j;
		}
		// if (quote)
		// 	i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
	print_token(*token);
}
*/

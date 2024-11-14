/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/14 03:26:00 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*addback(char *s1, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);
		s1 = NULL;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*set_arg(char *arg, char *line, int *i, t_env *env)
{
	int		j;
	char	*env_var;

	j = *i + 1;
	if (line[j] != '?')
		while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
			j++;
	else
		j++;
	j -= *i;
	if (j > 1)
	{
		env_var = ft_substr(line, *i + 1, j - 1);
		while (env)
		{
			if (!ft_strncmp(env->name, env_var, j - 1))
			{
				arg = ft_strjoin(arg, env->value);
				break ;
			}
			env = env->next;
		}
		free(env_var);
		env_var = NULL;
		(*i) += j - 1;
	}
	else
		arg = ft_strdup("$");
	return (arg);
}

char	*strarg(char *line, int *i, t_env *env)
{
	char	quote;
	char	*arg;
	// char	*tmp;

	quote = 0;
	arg = NULL;
	// tmp = NULL;
	while (line[*i])
	{
		if (line[*i] == quote)
		{
			quote = 0;
			(*i)++;
		}
		if (!quote && !end_check(line[*i]))
			break ;
		if (!quote && (line[*i] == '\'' || line[*i] == '\"'))
		{
			quote = line[*i];
			(*i)++;
			if (!check_quote(line, *i, quote, env))
				return (NULL);
		}
		if (line[*i] == '$' && quote != '\'')
			arg = set_arg(arg, line, i, env);
		else
		{
			// tmp = arg;
 			arg = addback(arg, line[*i]);
		}
		(*i)++;
	}
	return (arg);
}

int	set_index(char *line, int *i, t_env *env, t_token **token)
{
	char		*arg;
	static int	cmd = 0;

	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), HEREDOX));
		cmd = 0;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		lstadd_back(token, lstnew(ft_substr(line, *i, 2), APPEND));
		cmd = 0;
	}
	else if (line[*i] == '>')
	{
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), TRUNC));
		cmd = 0;
	}
	else if (line[*i] == '<')
	{
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), INPUT));
		cmd = 0;
	}
	else if (line[*i] == '|')
	{
		cmd = 1;
		lstadd_back(token, lstnew(ft_substr(line, *i, 1), PIPE));
	}
	else
	{
		arg = strarg(line, i, env);
		if (cmd || !(*token))
		{
			lstadd_back(token, lstnew(arg, CMD));
			cmd = 0;
		}
		else
		{
			if (lstlast(*token)->index == HEREDOX || lstlast(*token)->index == APPEND || lstlast(*token)->index == TRUNC || lstlast(*token)->index == INPUT)
				cmd = 1;
			lstadd_back(token, lstnew(arg, ARG));
		}
		// free(arg);
		// arg = NULL;
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/08 03:14:43 by nferrad          ###   ########.fr       */
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
	char	*tmp;
	char 	*tmp2;

	quote = 0;
	arg = NULL;
	while (line[*i])
	{
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
			tmp = ft_substr(line, *i, 1);
			tmp2 = ft_strjoin(arg, tmp);
			free(arg);
			arg = tmp2;
			free(tmp);
		}
		(*i)++;
		if (!line[*i])
			break;
		if (line[*i] == quote)
		{
			quote = 0;
			(*i)++;
		}
		if (!quote && !end_check(line[*i]))
			break ;
	}
	return (arg);
}

int	set_index(char *line, int *i, t_env *env, t_token **token)
{
	char	*arg;
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
	else if (cmd || *token == NULL)
	{
		int	j;
		j = *i;
		while (line[*i] && end_check(line[*i]))
			(*i)++;
		printf("fin : %d\n", *i);
		lstadd_back(token, lstnew(ft_substr(line, j, *i - j), CMD));
		cmd = 0;
	}
	else
	{
		arg = strarg(line, i, env);
		if (!arg)
			return (0);
		if (lstlast(*token)->index == HEREDOX || lstlast(*token)->index == APPEND || lstlast(*token)->index == TRUNC || lstlast(*token)->index == INPUT)
			cmd = 1;
		lstadd_back(token, lstnew(arg, ARG));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:33:27 by nferrad           #+#    #+#             */
/*   Updated: 2024/11/15 22:38:43 by nferrad          ###   ########.fr       */
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

char	*check_env_variable(t_env *env, char *arg, char *env_var, int j)
{
	while (env)
	{
		if (!ft_strncmp(env->name, env_var, j - 1))
		{
			arg = ft_strjoin(arg, env->value);
			break ;
		}
		env = env->next;
	}
	return (arg);
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
		arg = check_env_variable(env, arg, env_var, j);
		free(env_var);
		env_var = NULL;
		(*i) += j - 1;
	}
	else
		arg = ft_strdup("$");
	return (arg);
}

int	last_quote(char *quote, char *line, int *i)
{
	if (line[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		if (*i == (int)ft_strlen(line))
			return (0);
	}
	return (1);
}

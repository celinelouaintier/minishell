/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:34:52 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/09 17:26:16 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define CMD		1
# define ARG		2
# define PIPE		3
# define HEREDOX	4
# define APPEND		5
# define INPUT		6
# define TRUNC		7
# define FILE		8

typedef struct s_token
{
	char			*str;
	int				index;
	struct s_token	*next;
}					t_token;

void	parsing(char *line, t_token **token);

#endif
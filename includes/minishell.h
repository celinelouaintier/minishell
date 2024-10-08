/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:34:52 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/08 18:59:09 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define CMD	1
# define ARG	2
# define PIPE	3

typedef struct s_token
{
	char			*str;
	int				index;
	struct s_token	*next;
}					t_token;

#endif
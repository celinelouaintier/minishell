/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:34:52 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/23 19:57:11 by nferrad          ###   ########.fr       */
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

typedef struct s_token
{
	char			*str;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
	
}					t_token;

typedef struct s_exec
{
	int		**pipe_fd;
	int		pipe_num;
	char	**env;
}				t_exec;


typedef struct s_env
{
	char	*pwd;
}					t_env;

void	parsing(char *line, t_token **token);
void	cd(t_token *token, t_env *envp);
void	lstadd_back(t_token **lst, t_token *new);
void	echo(t_token *token);
t_token	*lstnew(char *content, int index);
t_token	*lstlast(t_token *lst);
char	**init_args(t_token *token);
char	*get_command_path(char *command);
void 	free_tokens(t_token **token);
void	ft_free(char **array);
void	process_pipes(t_token *token, char *env[]);
void	exec_builtin(t_token *token, t_env *envp, char **env);
int		is_builtin(t_token *token);
void	ft_exit(t_token *token);
int 	count_pipes(t_token *token);
void    ft_env(char **envp);
void	handle_redirections(t_token *token, int *saved_stdout);
void	exec(char **args, char *env[]);
void	restore_stdout(int *saved_stdout);
void	child_process(t_token *token, t_exec *execp, int i, char *env[]);
void	close_pipes(int **pipes_fd, int pipes_num, int cmd);

#endif
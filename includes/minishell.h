/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:34:52 by clouaint          #+#    #+#             */
/*   Updated: 2024/10/30 23:08:56 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/*		Errors			*/

# define ERR_ENV	"\033[0;31m\x1b[1mError :\033[0m \
Cannot open the shell without env.\n"
# define ERR_NL	"\033[0;31m\x1b[1mError :\033[0m \
Syntax error near unexpected token `newline'.\n"
# define ERR_STX	"\033[0;31m\x1b[1mError :\033[0m \
Syntax error near unexpected token `%s'.\n"
# define ERR_QUOTE	"\033[0;31m\x1b[1mError :\033[0m \
Unclosed quote, expected (%c) in your argument.\n"

/*		Token index		*/

# define CMD		1
# define ARG		2
# define PIPE		3
# define HEREDOX	4
# define APPEND		5
# define INPUT		6
# define TRUNC		7

/*		Structures		*/

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
	int		saved_stdout;
}				t_exec;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

/*		Parsing			*/

void	parsing(char *line, t_token **token, t_env *env);
void	add_command(char *line, int *i, t_token **token);
int		end_check(char c);
int		check_quote(char *line, int i, char quote);

/*		Token			*/

void	lstadd_back(t_token **lst, t_token *new);
t_token	*lstnew(char *content, int index);
t_token	*lstlast(t_token *lst);
void	free_tokens(t_token **token);

/*		Execution		*/

void	process_pipes(t_token *token, t_env **envp);
void	exec_builtin(t_token *token, t_env **env, int fd, t_exec *exec);
int		is_builtin(t_token *token);
void	handle_redirections(t_token *token, t_exec *exec);
void	exec(char **args, t_env **envp);
void	child_process(t_token *token, t_exec *execp, int i, t_env **envp);
void	close_pipes(int **pipes_fd, int pipes_num, int cmd);
void	restore_stdout(int *saved_stdout);
int		**create_pipes(int pipes_num);
t_exec	init_exec(t_token *token);

/*		Builtins		*/

void	ft_cd(t_token *token, t_env **envp);
void	echo(t_token *token, int fd);
void	ft_exit(t_token *token);
void	ft_export(t_token *token, t_env **envp);
void	print_env(t_env *env);

/* 		Environment		*/

t_env	*init_env(char **env);
t_env	*add_env_var(char *env_var);
t_env	*sync_env(t_env *child_env);

/*		Utils			*/

char	**init_args(t_token *token);
char	*get_command_path(char *command);
void	ft_free(char **array);
int		count_pipes(t_token *token);
char	**lst_to_array(t_env **env);

void	here_doc(char *limiter);

#endif
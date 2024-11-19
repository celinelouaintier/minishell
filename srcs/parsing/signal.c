/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:13:45 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/08 02:48:48 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

void	cmd_sig_handler(int signum)
{
	g_sig = signum;
	if (signum == SIGINT)
		ft_printf("\n");
	else if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
}

char	*set_line(char *line, t_env *envp)
{
	set_sig();
	line = readline("\001\033[0;34m\x1b[1m\002Minishell> \001\033[0m\002");
	if (g_sig)
	{
		update_exit_status(envp, g_sig + 128);
		g_sig = 0;
	}
	return (line);
}

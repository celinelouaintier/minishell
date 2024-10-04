/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 14:54:04 by clouaint          #+#    #+#             */
/*   Updated: 2024-10-02 14:54:04 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *line, int fd, int flag)
{
	if (!flag)
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd(line, fd);
}

int main(int argc, char *argv[])
{
	char *path = getenv("PWD");
	ft_printf("%s\n", path);
	if (argc <= 1)
		return (-1);
	if (!ft_strncmp(argv[1], "echo", 5))
		echo(argv[2], atoi(argv[3]), atoi(argv[4]));
	else if (!ft_strncmp(argv[1], "pwd", 4))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(argv[1], "cd", 3))
	{
		chdir(argv[2]); // ca marche pas du tout
		ft_printf("%s\n", getcwd(NULL, 0));
		// getcwd(argv[5], sizeof(argv[5]));
	}
	return (-1);
}

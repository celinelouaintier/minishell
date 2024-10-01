/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:16:21 by nferrad           #+#    #+#             */
/*   Updated: 2024/08/03 20:31:34 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *stash, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*clean_line(char *line)
{
	char	*new_line;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	new_line = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!*new_line)
	{
		free(new_line);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*res;
	static char	*stash[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	buf = malloc(BUFFER_SIZE + 1);
	res = read_line(fd, stash[fd], buf);
	free(buf);
	if (!res)
		return (NULL);
	stash[fd] = clean_line(res);
	return (res);
}

// int	main(int argc, char **argv)
// {
// 	int	fd;
// 	char *dest;
// 	fd = open(argv[1], O_RDONLY);
// 	printf("fd : %d\n content : %s\n", fd, dest = get_next_line(fd));
// 	// ft_printf("Here !");
// 	free(dest);
// 	printf("fd : %d\n content : %s\n", fd, dest = get_next_line(fd));
// 	free(dest);

// 	return (argc);
// }
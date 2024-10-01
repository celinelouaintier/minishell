/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:20:31 by nferrad           #+#    #+#             */
/*   Updated: 2024/05/22 16:20:34 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s;

	len = ft_strlen(s1);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	while (len-- > 0)
		s[len] = s1[len];
	return (s);
}

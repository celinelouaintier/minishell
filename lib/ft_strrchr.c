/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:27:17 by nferrad           #+#    #+#             */
/*   Updated: 2024/05/22 16:27:21 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			p = (char *)(s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		p = (char *)(s + i);
	return (p);
}

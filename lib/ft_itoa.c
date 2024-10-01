/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:25:28 by nferrad           #+#    #+#             */
/*   Updated: 2024/05/26 16:33:38 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	lennbr(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*stocknbr(int n, char *arg, int len, int neg)
{
	int	tmp;

	tmp = n;
	arg[len] = '\0';
	len--;
	while (len >= 0)
	{
		arg[len] = (n % 10) + '0';
		n /= 10;
		if (neg && !len)
			arg[len] = '-';
		if (tmp == 147483648)
		{
			arg[0] = '-';
			arg[1] = '2';
		}
		len--;
	}
	return (arg);
}

char	*ft_itoa(int n)
{
	char	*arg;
	int		len;
	int		neg;

	len = 0;
	neg = 0;
	if (n == -2147483648)
	{
		len = 2;
		n = 147483648;
	}
	if (n <= 0)
	{
		len = 1;
		if (n < 0)
			neg = 1;
		n *= -1;
	}
	len += lennbr(n);
	arg = malloc(len * sizeof(char) + 1);
	if (!arg)
		return (NULL);
	arg = stocknbr(n, arg, len, neg);
	return (arg);
}

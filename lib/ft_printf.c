/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:20 by nferrad           #+#    #+#             */
/*   Updated: 2024/07/02 21:47:21 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	if (!c)
		return (write(1, "(null)", 6));
	else
		return (write(1, &c, 1));
}

int	ft_printstr(const char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	else
		return (write(1, str, ft_strlen(str)));
}

static int	ft_printnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		n = 147483648;
		len += ft_printchar('-');
		len += ft_printchar('2');
	}
	if (n < 0)
	{
		len += ft_printchar('-');
		n *= -1;
	}
	if (n < 10)
		len += ft_printchar(n + '0');
	else
	{
		len += ft_printnbr(n / 10);
		len += ft_printchar((n % 10) + '0');
	}
	return (len);
}

int	check_format(char c, va_list ap)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	else if (c == 's')
		return (ft_printstr(va_arg(ap, char *)));
	else if (c == 'i' || c == 'd')
		return (ft_printnbr(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_printunbr(va_arg(ap, unsigned int)));
	else if (c == 'x')
		return (ft_print_hexa(va_arg(ap, unsigned int),
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_print_hexa(va_arg(ap, unsigned int),
				"0123456789ABCDEF"));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(ap, unsigned long long)));
	else if (c == '%')
		return (ft_printchar('%'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	va_start(ap, str);
	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += check_format(str[i + 1], ap);
			i++;
		}
		else
			len += ft_printchar(str[i]);
		i++;
	}
	return (len);
}

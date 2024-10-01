/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:58:10 by nferrad           #+#    #+#             */
/*   Updated: 2024/07/02 21:46:16 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_ptr(uintptr_t nb)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	if (nb >= 16)
	{
		len += ft_put_ptr(nb / 16);
		len += ft_put_ptr(nb % 16);
	}
	else
		len += ft_printchar(base[nb]);
	return (len);
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	len;

	if (ptr == 0)
	{
		ft_printstr("(nil)");
		return (5);
	}
	len = ft_printstr("0x");
	len += ft_put_ptr(ptr);
	return (len);
}

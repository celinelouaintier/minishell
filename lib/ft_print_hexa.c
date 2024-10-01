/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:24:01 by nferrad           #+#    #+#             */
/*   Updated: 2024/07/02 21:46:23 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa(unsigned int nb, char *base)
{
	int		len;

	len = 0;
	if (nb < 16)
		len += ft_printchar(base[nb]);
	else
	{
		len += ft_print_hexa(nb / 16, base);
		len += ft_printchar(base[nb % 16]);
	}
	return (len);
}

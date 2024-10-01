/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:27:55 by nferrad           #+#    #+#             */
/*   Updated: 2024/07/02 21:46:01 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 10)
		len += ft_printchar(n + '0');
	else
	{
		len += ft_printunbr(n / 10);
		len += ft_printchar((n % 10) + '0');
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:21:15 by gsantill          #+#    #+#             */
/*   Updated: 2024/10/04 09:34:08 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *ptr)
{
	unsigned long long	address;
	int					count;

	address = (unsigned long long)ptr;
	if (address == 0)
	{
		(write(1, "(nil)", 5));
		return (5);
	}
	write(1, "0x", 2);
	count = ft_print_hex(address, 'x');
	return (count + 2);
}

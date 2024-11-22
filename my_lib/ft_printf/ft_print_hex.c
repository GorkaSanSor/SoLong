/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:46 by gsantill          #+#    #+#             */
/*   Updated: 2024/10/04 11:21:15 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long long num, char may_min)
{
	char	buffer[16];
	int		count;
	int		len;

	count = 0;
	if (num == 0)
		return (write(1, "0", 1));
	while (num > 0)
	{
		if (may_min == 'x')
			buffer[count++] = "0123456789abcdef"[num % 16];
		else if (may_min == 'X')
			buffer[count++] = "0123456789ABCDEF"[num % 16];
		num /= 16;
	}
	len = count;
	while (count--)
		write(1, &buffer[count], 1);
	return (len);
}

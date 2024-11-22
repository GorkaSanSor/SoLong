/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:52:20 by gsantill          #+#    #+#             */
/*   Updated: 2024/10/04 09:27:17 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_itoa_buffer(unsigned int num, char *buffer)
{
	int	len;

	len = 0;
	if (num == 0)
		buffer[len++] = '0';
	while (num > 0)
	{
		buffer[len++] = (num % 10) + '0';
		num = num / 10;
	}
	return (len);
}

int	ft_print_nbr(int num, char sign)
{
	char			buffer[12];
	int				len;
	int				len_orig;
	unsigned int	n;

	if (sign == 'u')
		n = (unsigned int)num;
	else
		n = num;
	if (sign == 's' && num < 0)
	{
		write(1, "-", 1);
		n = -num;
	}
	len = ft_itoa_buffer(n, buffer);
	len_orig = len;
	while (len > 0)
		write(1, &buffer[--len], 1);
	return (len_orig + (num < 0 && sign == 's'));
}

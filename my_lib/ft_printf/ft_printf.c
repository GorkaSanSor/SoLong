/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:47:32 by gsantill          #+#    #+#             */
/*   Updated: 2024/10/04 11:31:52 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static size_t	ft_check_param(char const *param, size_t count, va_list args)
{
	if (*param == 'd' || *param == 'i')
		count += ft_print_nbr(va_arg(args, int), 's');
	else if (*param == 'u')
		count += ft_print_nbr(va_arg(args, unsigned int), 'u');
	else if (*param == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (*param == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (*param == '%')
		count += write(1, "%", 1);
	else if (*param == 'p')
		count += ft_print_pointer(va_arg(args, void *));
	else if (*param == 'x' || *param == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), *param);
	return (count);
}

int	ft_printf(const char *param, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, param);
	while (param[i] != '\0')
	{
		if (param[i] != '%')
		{
			write(1, &param[i], 1);
			count++;
		}
		else if (param[i] == '%')
			count = ft_check_param(&param[++i], count, args);
		i++;
	}
	va_end(args);
	return (count);
}

/*int	main(void)
{
	char *str = "hola";
	int num	= 42;
	unsigned int unsigned_num = 3000000000;

	ft_printf("Numero: %d, Caracter: %c, Porcentaje: %%\n", 42, 'A');
	printf("Numero_og: %d, Caracter_og: %c, Porcentaje_og: %%\n\n", 42, 'A');

	ft_printf("Entero en base 10: %i\n", -123);
	printf("Entero en base 10 _og: %i\n\n", -123);

	ft_printf("Número sin signo: %u\n", unsigned_num);
	printf("Número sin signo _og: %u\n\n", unsigned_num);
	
	ft_printf("String: %s\n", str);
	printf("String_og: %s\n\n", str);
	
	ft_printf("Puntero de la variable num: %p\n", &num);
	printf("Puntero de la variable num_og: %p\n\n", &num);
	
	ft_printf("Puntero de la variable hex: %x\n", num);
	printf("Puntero de la variable hex_og: %x\n\n", num);
	
	ft_printf("Puntero de la variable HEX: %X\n", num);
	printf("Puntero de la variable HEX_OG: %X\n\n", num);
	return (0);
}*/

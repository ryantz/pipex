/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:29:55 by ryatan            #+#    #+#             */
/*   Updated: 2025/12/03 10:25:28 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_process_specifier(va_list args, const char *format, int *count)
{
	if (*format == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (*format == 'c')
		ft_putchar((char)va_arg(args, int), count);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (*format == 'x')
		ft_puthex(va_arg(args, unsigned int), 'l', count);
	else if (*format == 'X')
		ft_puthex(va_arg(args, unsigned int), 'u', count);
	else if (*format == 'p')
		ft_putpointer(va_arg(args, void *), count);
	else if (*format == 'u')
		ft_putunbr(va_arg(args, unsigned int), count);
	else if (*format == '%')
		ft_putchar('%', count);
	else
	{
		ft_putchar('%', count);
		ft_putchar(*format, count);
	}
}

void	ft_process_format(va_list args, const char *format, int *count)
{
	while (*format)
	{
		if (*format == '%' && (*format + 1))
		{
			format++;
			ft_process_specifier(args, format, count);
		}
		else
			ft_putchar(*format, count);
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	ft_process_format(args, format, &count);
	va_end(args);
	return (count);
}

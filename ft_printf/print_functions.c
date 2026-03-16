/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:21:44 by ryatan            #+#    #+#             */
/*   Updated: 2025/12/02 21:59:57 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr(unsigned int nb, int *count)
{
	unsigned long	lnb;
	char			cnb;

	lnb = nb;
	if (lnb <= 9)
	{
		cnb = lnb + '0';
		ft_putchar(cnb, count);
	}
	else
	{
		ft_putunbr(lnb / 10, count);
		ft_putunbr(lnb % 10, count);
	}
}

void	ft_puthex(unsigned int in, char casing, int *count)
{
	unsigned long	l_in;
	char			c_in;
	char			*hex_range_upper;
	char			*hex_range_lower;

	l_in = in;
	c_in = '\0';
	hex_range_lower = "0123456789abcdef";
	hex_range_upper = "0123456789ABCDEF";
	if (l_in < 16)
	{
		if (casing == 'l')
			c_in = hex_range_lower[l_in];
		else if (casing == 'u')
			c_in = hex_range_upper[l_in];
		ft_putchar(c_in, count);
	}
	else if (l_in >= 16)
	{
		ft_puthex(l_in / 16, casing, count);
		ft_puthex(l_in % 16, casing, count);
	}
}

static void	ft_puthex_long(unsigned long ptr, int *count)
{
	char			*hex_range;
	char			c_in;

	hex_range = "0123456789abcdef";
	if (ptr < 16)
	{
		c_in = hex_range[ptr];
		ft_putchar(c_in, count);
	}
	else if (ptr >= 16)
	{
		ft_puthex_long(ptr / 16, count);
		ft_puthex_long(ptr % 16, count);
	}
}

void	ft_putpointer(void *ptr, int *count)
{
	if (!ptr)
	{
		ft_putstr("(nil)", count);
	}
	else
	{
		ft_putchar('0', count);
		ft_putchar('x', count);
		ft_puthex_long((unsigned long)ptr, count);
	}
}

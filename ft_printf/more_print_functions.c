/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_print_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:57:20 by ryatan            #+#    #+#             */
/*   Updated: 2026/02/19 13:26:58 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printf_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr(char *str, int *count)
{
	size_t	i;
	char	*null;

	i = 0;
	null = "(null)";
	if (!str)
	{
		while (i < 6)
		{
			ft_putchar(null[i], count);
			i++;
		}
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

void	ft_putnbr(int nb, int *count)
{
	long	lnb;
	char	cnb;

	lnb = nb;
	if (lnb < 0)
	{
		ft_putchar('-', count);
		lnb *= -1;
	}
	if (lnb >= 0 && lnb <= 9)
	{
		cnb = lnb + '0';
		ft_putchar(cnb, count);
	}
	else
	{
		ft_putnbr(lnb / 10, count);
		ft_putnbr(lnb % 10, count);
	}
}

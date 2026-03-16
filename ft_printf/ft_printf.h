/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:30:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/02/19 13:27:20 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

//printing fn
void	ft_puthex(unsigned int in, char casing, int *count);
void	ft_putpointer(void *ptr, int *count);
void	ft_putunbr(unsigned int nb, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putchar(char c, int *count);
void	ft_putnbr(int nb, int *count);

size_t	ft_printf_strlen(const char *s);

// main printf
int		ft_printf(const char *format, ...);

#endif

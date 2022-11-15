/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:55:57 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/02 17:00:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_param(char pc, char c, va_list args, int *nb_char_print)
{
	if (c == 'c')
		ft_print_char(va_arg(args, int), nb_char_print);
	else if (c == 's')
		ft_print_string(va_arg(args, char *), nb_char_print);
	else if (c == 'd' || c == 'i')
		ft_print_int(va_arg(args, int), nb_char_print);
	else if (c == 'u')
		ft_print_uint(va_arg(args, unsigned int), nb_char_print);
	else if (c == 'x')
		ft_print_lowerhex(va_arg(args, unsigned int), nb_char_print);
	else if (c == 'X')
		ft_print_upperhex(va_arg(args, unsigned int), nb_char_print);
	else if (c == 'p')
		ft_print_pointer(va_arg(args, void *), nb_char_print);
	else if (c == '%')
		ft_print_char(c, nb_char_print);
	else
	{
		ft_print_char(pc, nb_char_print);
		ft_print_char(c, nb_char_print);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		nb_char_print;

	va_start(args, str);
	i = 0;
	nb_char_print = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			print_param(str[i], str[i + 1], args, &nb_char_print);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			nb_char_print++;
		}
		i++;
	}
	va_end(args);
	return (nb_char_print);
}

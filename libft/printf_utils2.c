/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:58:18 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/02 17:06:19 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_hex(unsigned int nb, char *base)
{
	if (nb >= 16)
		print_hex(nb / 16, base);
	ft_putchar_fd(base[nb % 16], 1);
}

char	*itoa_hex(size_t nb, char *base, char *str)
{
	char	*res;
	int		i;

	if (nb >= 16)
		str = itoa_hex(nb / 16, base, str);
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = base[nb % 16];
	res[i + 1] = '\0';
	free(str);
	return (res);
}

void	ft_print_lowerhex(unsigned int nb, int *nb_char_print)
{
	unsigned int	tmp;
	int				cpt;

	cpt = 0;
	tmp = nb;
	while (tmp >= 16)
	{
		tmp /= 16;
		cpt++;
	}
	cpt++;
	print_hex(nb, "0123456789abcdef");
	*nb_char_print += cpt;
}

void	ft_print_upperhex(unsigned int nb, int *nb_char_print)
{
	unsigned int	tmp;
	int				cpt;

	cpt = 0;
	tmp = nb;
	while (tmp >= 16)
	{
		tmp /= 16;
		cpt++;
	}
	cpt++;
	print_hex(nb, "0123456789ABCDEF");
	*nb_char_print += cpt;
}

void	ft_print_pointer(void *p, int *nb_char_print)
{
	char	*res;
	int		len;

	if (p == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		*nb_char_print += 5;
		return ;
	}
	res = malloc(sizeof(char));
	if (res == NULL)
		return ;
	res[0] = '\0';
	res = itoa_hex((size_t)p, "0123456789abcdef", res);
	len = ft_strlen(res);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(res, 1);
	free(res);
	*nb_char_print += len + 2;
}

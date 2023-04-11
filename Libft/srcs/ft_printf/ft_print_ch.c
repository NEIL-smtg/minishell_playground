/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:06:02 by suchua            #+#    #+#             */
/*   Updated: 2022/10/29 19:06:02 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_rep(int rep, char c)
{
	while (rep > 0)
	{
		write(1, &c, 1);
		rep--;
	}
}

int	ft_print_ch(char c, t_flag *flags)
{
	int	len;

	len = 1;
	if (!flags->minus && flags->width)
	{
		if (flags->zero)
			ft_print_rep(flags->width - len, '0');
		else
			ft_print_rep(flags->width - len, 32);
		len = flags->width;
	}
	else if (c == '%' && flags->dot && flags->precision)
	{
		ft_print_rep(flags->precision - len, '0');
		len = flags->precision;
	}
	write(1, &c, 1);
	if (flags->minus && flags->width)
	{
		ft_print_rep(flags->width - len, 32);
		len = flags->width;
	}
	return (len);
}

static int	ft_get_prec(int precision, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (precision < len && !str)
		return (0);
	if (precision < len)
		len = precision;
	return (len);
}

static int	ft_get_width(int str_len, int width, t_flag *flags)
{
	if (width > str_len)
	{
		if (flags->zero && !flags->minus)
			ft_print_rep(width - str_len, '0');
		else
			ft_print_rep(width - str_len, 32);
		return (width - str_len);
	}
	return (0);
}

int	ft_print_str(char *str, t_flag *flags)
{
	int		str_len;
	int		len;
	char	*nullstr;

	nullstr = "(null)";
	if (!str)
		str = nullstr;
	str_len = ft_strlen(str);
	len = 0;
	if (flags->dot)
		str_len = ft_get_prec(flags->precision, str);
	if (flags->width && !flags->minus)
		len += ft_get_width(str_len, flags->width, flags);
	if (!str)
		write(1, nullstr, str_len);
	else
		write(1, str, str_len);
	if (flags->width && flags->minus)
		len += ft_get_width(str_len, flags->width, flags);
	return (len + str_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:26:44 by suchua            #+#    #+#             */
/*   Updated: 2022/10/31 23:26:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_hex_nbrlen(unsigned long nb)
{
	int	nbrlen;

	nbrlen = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nbrlen++;
		nb /= 16;
	}
	return (nbrlen);
}

static int	ft_handle_prec(t_flag *flags, unsigned long nb, int print)
{
	int	len;

	if (nb == 0 && flags->dot && !flags->precision)
		return (0);
	len = flags->precision - ft_get_hex_nbrlen(nb);
	if (print)
		ft_print_rep(len, '0');
	if (len > 0)
		return (len);
	return (0);
}

static int	ft_handle_width(t_flag *flags, unsigned long nb)
{
	int	nbrlen;
	int	curr_width;

	nbrlen = ft_get_hex_nbrlen(nb);
	if (nb == 0 && !flags->precision && flags->dot)
		nbrlen = 0;
	curr_width = ft_handle_prec(flags, nb, 0) + nbrlen;
	if (flags->width > curr_width && flags->zero && !flags->dot)
		ft_print_rep(flags->width - curr_width, '0');
	else
		ft_print_rep(flags->width - curr_width, 32);
	if (flags->width > curr_width)
		return (flags->width - curr_width);
	return (0);
}

static int	ft_handle_pw(t_flag *flags, unsigned long nb, int type)
{
	int	curr_width;
	int	nbrlen;

	nbrlen = ft_get_hex_nbrlen(nb);
	curr_width = ft_handle_prec(flags, nb, 0) + nbrlen;
	if (nb == 0 && !flags->precision && flags->dot)
		curr_width--;
	if (flags->width > curr_width)
	{
		if (!flags->minus)
			ft_handle_width(flags, nb);
		ft_handle_prec(flags, nb, PRINT);
		if (flags->hash)
			ft_write_prefix(type);
		ft_before_print_hex(flags, nb, type);
		if (flags->minus)
			ft_handle_width(flags, nb);
		return (flags->width);
	}
	else
	{
		ft_handle_prec(flags, nb, PRINT);
		ft_before_print_hex(flags, nb, type);
		return (curr_width);
	}
}

int	ft_print_hex_central(unsigned long nb, t_flag *flags, int type)
{
	int	len;

	if (flags->dot && flags->width)
		return (ft_handle_pw(flags, nb, type));
	len = 0;
	if (flags->width && !flags->minus)
		len += ft_handle_width(flags, nb);
	else if (flags->dot)
		len += ft_handle_prec(flags, nb, PRINT);
	len += ft_before_print_hex(flags, nb, type);
	if (flags->width && flags->minus)
		len += ft_handle_width(flags, nb);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_usnb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 00:42:02 by suchua            #+#    #+#             */
/*   Updated: 2022/10/30 00:42:02 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_usnbrlen(unsigned int nb)
{
	int	nbrlen;

	nbrlen = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nbrlen++;
		nb /= 10;
	}
	return (nbrlen);
}

static int	ft_handle_prec(t_flag *flags, unsigned int nb, int print)
{
	int	len;

	if (nb == 0 && flags->dot && !flags->precision)
		return (0);
	len = flags->precision - ft_get_usnbrlen(nb);
	if (print)
		ft_print_rep(len, '0');
	if (len > 0)
		return (len);
	return (0);
}

static int	ft_handle_width(t_flag *flags, unsigned int nb)
{
	int	nbrlen;
	int	curr_width;

	nbrlen = ft_get_usnbrlen(nb);
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

static int	ft_handle_pw(t_flag *flags, unsigned int nb)
{
	int	curr_width;
	int	nbrlen;

	nbrlen = ft_get_usnbrlen(nb);
	curr_width = ft_handle_prec(flags, nb, 0) + nbrlen;
	if (nb == 0 && !flags->precision && flags->dot)
		curr_width--;
	if (flags->width > curr_width)
	{
		if (!flags->minus)
			ft_handle_width(flags, nb);
		ft_handle_prec(flags, nb, PRINT);
		ft_before_print_usnb(flags, nb, nbrlen);
		if (flags->minus)
			ft_handle_width(flags, nb);
		return (flags->width);
	}
	else
	{
		ft_handle_prec(flags, nb, PRINT);
		ft_before_print_usnb(flags, nb, nbrlen);
		return (curr_width);
	}
}

int	ft_usnb_central(unsigned int nb, t_flag *flags)
{
	int	len;

	if (flags->dot && flags->width)
		return (ft_handle_pw(flags, nb));
	len = 0;
	if (flags->width && !flags->minus)
		len += ft_handle_width(flags, nb);
	else if (flags->dot)
		len += ft_handle_prec(flags, nb, PRINT);
	else if (flags->plus || flags->space)
		len += ft_print_us_plus_sp(flags);
	len += ft_before_print_usnb(flags, nb, ft_get_usnbrlen(nb));
	if (flags->width && flags->minus)
		len += ft_handle_width(flags, nb);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 00:57:26 by suchua            #+#    #+#             */
/*   Updated: 2022/10/30 00:57:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_nbrlen(unsigned long nbr)
{
	int	val;

	val = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		val++;
		nbr /= 16;
	}
	return (val);
}

static int	ft_print_width(t_flag *flags, int nbrlen)
{
	int	curr_width;
	int	prec;
	int	prefix;

	prec = 0;
	prefix = 2;
	if (flags->dot && !flags->precision)
		nbrlen = 0;
	if (flags->precision > nbrlen)
		prec = flags->precision - nbrlen;
	curr_width = prec + nbrlen + prefix;
	if (flags->width > curr_width)
	{
		ft_print_rep(flags->width - curr_width, 32);
		return (flags->width - curr_width);
	}
	return (0);
}

static int	ft_handle_prec(t_flag *flags, int nbrlen)
{
	if (flags->precision > nbrlen)
	{
		ft_print_rep(flags->precision - nbrlen, '0');
		return (flags->precision - nbrlen);
	}
	return (0);
}

int	ft_print_address(void *content, t_flag *flags)
{
	unsigned long	address;
	int				nbrlen;
	int				len;

	address = (unsigned long) content;
	nbrlen = ft_get_nbrlen(address);
	len = 0;
	if (flags->width && !flags->minus)
		len += ft_print_width(flags, nbrlen);
	write(1, "0x", 2);
	len += 2;
	if (flags->dot)
		len += ft_handle_prec(flags, nbrlen);
	if (!(flags->dot && !flags->precision))
	{
		ft_print_hex(address, LOWER);
		len += nbrlen;
	}
	if (flags->width && flags->minus)
		len += ft_print_width(flags, nbrlen);
	return (len);
}

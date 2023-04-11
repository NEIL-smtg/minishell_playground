/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:57:41 by suchua            #+#    #+#             */
/*   Updated: 2022/11/04 16:57:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_prec(t_flag *flags, char *nbrstr, int print)
{
	int	len;

	if (*nbrstr == '0' && flags->dot && !flags->precision)
		return (0);
	len = flags->precision - ft_strlen(nbrstr);
	if (*nbrstr == '-')
		len++;
	if (print)
	{
		if (*nbrstr == '-')
			write(1, "-", 1);
		ft_print_rep(len, '0');
	}
	if (len > 0)
		return (len);
	return (0);
}

static int	ft_handle_width(t_flag *flags, char *nbrstr)
{
	int	nbrlen;
	int	curr_width;

	nbrlen = ft_strlen(nbrstr);
	if (*nbrstr == '0' && !flags->precision && flags->dot)
		nbrlen = 0;
	curr_width = ft_handle_prec(flags, nbrstr, 0) + nbrlen;
	if (flags->width > curr_width && flags->zero && !flags->dot)
	{
		if (!flags->dot && *nbrstr == '-' && !flags->minus)
			write(1, "-", 1);
		ft_print_rep(flags->width - curr_width, '0');
	}
	else
	{
		ft_print_rep(flags->width - curr_width, 32);
		if (!flags->dot && *nbrstr == '-' && !flags->minus)
			write(1, "-", 1);
	}
	if (flags->width > curr_width)
		return (flags->width - curr_width);
	return (0);
}

static int	ft_handle_pw(t_flag *flags, char *nbrstr)
{
	int	curr_width;

	curr_width = ft_handle_prec(flags, nbrstr, 0) + ft_strlen(nbrstr);
	if (*nbrstr == '0' && !flags->precision && flags->dot)
		curr_width--;
	if (flags->width > curr_width)
	{
		if (!flags->minus)
			ft_handle_width(flags, nbrstr);
		ft_handle_prec(flags, nbrstr, PRINT);
		ft_print_nb(flags, nbrstr);
		if (flags->minus)
			ft_handle_width(flags, nbrstr);
		free(nbrstr);
		return (flags->width);
	}
	else
	{
		ft_handle_prec(flags, nbrstr, PRINT);
		ft_print_nb(flags, nbrstr);
		free(nbrstr);
		return (curr_width);
	}
}

int	ft_nb_central(int nbr, t_flag *flags)
{
	char	*nbrstr;
	int		len;

	nbrstr = ft_itoa(nbr);
	if (flags->dot && flags->width)
		return (ft_handle_pw(flags, nbrstr));
	len = 0;
	if (flags->width && !flags->minus)
		len += ft_handle_width(flags, nbrstr);
	else if (flags->dot)
		len += ft_handle_prec(flags, nbrstr, PRINT);
	else if (flags->plus || flags->space)
		len += ft_print_plus_sp(flags, nbrstr);
	len += ft_print_nb(flags, nbrstr);
	if (flags->width && flags->minus)
		len += ft_handle_width(flags, nbrstr);
	free(nbrstr);
	return (len);
}

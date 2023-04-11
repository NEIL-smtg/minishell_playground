/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_usnb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:51:24 by suchua            #+#    #+#             */
/*   Updated: 2022/10/31 18:51:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_us_plus_sp(t_flag *flags)
{
	if (flags->space && !flags->plus)
		write(1, " ", 1);
	else if (flags->plus && !flags->space)
		write(1, "+", 1);
	else
		return (0);
	return (1);
}

int	ft_before_print_usnb(t_flag *flags, unsigned int nbr, int nbrlen)
{
	if (nbr == 0 && flags->dot && !flags->precision)
		return (0);
	ft_print_usnb(nbr);
	return (nbrlen);
}

void	ft_print_usnb(unsigned int nbr)
{
	char	ch;

	if (nbr / 10 > 0)
	{
		ft_print_usnb(nbr / 10);
		ch = nbr % 10 + '0';
		write(1, &ch, 1);
	}
	else
	{
		ch = nbr + '0';
		write(1, &ch, 1);
	}
}

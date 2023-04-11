/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:49:34 by suchua            #+#    #+#             */
/*   Updated: 2022/11/01 16:49:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_before_print_hex(t_flag *flags, unsigned long nb, int type)
{
	int	len;

	len = 0;
	if (nb == 0 && flags->dot && !flags->precision)
		return (0);
	if (flags->hash && nb != 0)
	{
		ft_write_prefix(type);
		len += 2;
	}
	ft_print_hex(nb, type);
	return (ft_get_hex_nbrlen(nb) + len);
}

void	ft_write_prefix(int type)
{
	if (type == LOWER)
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
}

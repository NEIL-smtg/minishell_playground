/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:19:57 by suchua            #+#    #+#             */
/*   Updated: 2022/11/10 18:04:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(unsigned long address, int type)
{
	char	*base;

	if (type == LOWER)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (address >= 16)
	{
		ft_print_hex(address / 16, type);
		write(1, &base[address % 16], 1);
	}
	else
		write(1, &base[address], 1);
}

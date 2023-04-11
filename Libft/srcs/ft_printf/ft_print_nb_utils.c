/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:31:06 by suchua            #+#    #+#             */
/*   Updated: 2022/11/04 17:31:06 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_plus_sp(t_flag *flags, char *nbrstr)
{
	if (flags->space && !flags->plus && *nbrstr != '-')
		write(1, " ", 1);
	else if (flags->plus && *nbrstr != '-' && !flags->space)
		write(1, "+", 1);
	else
		return (0);
	return (1);
}

int	ft_print_nb(t_flag *flags, char *nbrstr)
{
	if (*nbrstr == '0' && !flags->precision && flags->dot)
		return (0);
	if (*nbrstr == '-')
	{
		if (flags->dot)
			ft_putstr_fd(nbrstr + 1, 1);
		else if (flags->width && !flags->minus)
			ft_putstr_fd(nbrstr + 1, 1);
		else
			ft_putstr_fd(nbrstr, 1);
	}
	else
		ft_putstr_fd(nbrstr, 1);
	return (ft_strlen(nbrstr));
}

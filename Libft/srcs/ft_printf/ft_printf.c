/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:41:12 by suchua            #+#    #+#             */
/*   Updated: 2023/04/01 05:32:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// sp = specifier cspdiuxX%
int	ft_print_all(t_flag *flags, va_list args, char sp)
{
	if (sp == 'c')
		return (ft_print_ch(va_arg(args, int), flags));
	else if (sp == 's')
		return (ft_print_str(va_arg(args, char *), flags));
	else if (sp == 'p')
		return (ft_print_address(va_arg(args, void *), flags));
	else if (sp == 'd' || sp == 'i')
		return (ft_nb_central(va_arg(args, int), flags));
	else if (sp == 'u')
		return (ft_usnb_central(va_arg(args, unsigned int), flags));
	else if (sp == 'x')
		return (ft_print_hex_central(va_arg(args, unsigned int), flags, LOWER));
	else if (sp == 'X')
		return (ft_print_hex_central(va_arg(args, unsigned int), flags, UPPER));
	else if (sp == '%')
		return (ft_print_ch(sp, flags));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	t_flag	*flags;
	int		len;

	flags = malloc(sizeof(t_flag));
	len = 0;
	i = -1;
	va_start(args, format);
	while (format[++i])
	{
		ft_set_flags(flags);
		if (format[i] == '%')
		{
			ft_get_flags(flags, format, &i);
			len += ft_print_all(flags, args, format[i]);
		}
		else
			len += ft_print_ch(format[i], flags);
		if (!format[i])
			break ;
	}
	free(flags);
	va_end(args);
	return (len);
}

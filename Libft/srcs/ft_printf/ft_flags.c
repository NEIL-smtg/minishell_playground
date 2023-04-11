/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:38:36 by suchua            #+#    #+#             */
/*   Updated: 2022/10/29 18:38:36 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_specifier(char c)
{
	char	*specifier;
	int		i;

	specifier = "cspdiuxX%";
	i = -1;
	while (specifier[++i])
	{
		if (c == specifier[i])
			return (1);
	}
	return (0);
}

static int	ft_get_width_prec(const char *format, int *i)
{
	int	width_prec;

	width_prec = ft_atoi(format + *i);
	while (ft_isdigit(format[*i]))
		(*i)++;
	return (width_prec);
}

void	ft_set_flags(t_flag	*flags)
{
	flags -> zero = 0;
	flags -> minus = 0;
	flags -> dot = 0;
	flags -> hash = 0;
	flags -> space = 0;
	flags -> plus = 0;
	flags -> width = 0;
	flags -> precision = 0;
}

void	ft_get_flags(t_flag *flags, const char *format, int *i)
{
	*i += 1;
	while (format[*i] && !check_specifier(format[*i]))
	{
		if (ft_isdigit(format[*i]) && format[*i] != '0')
		{
			flags->width = ft_get_width_prec(format, i);
			continue ;
		}
		if (format[*i] == '0')
			flags->zero = 1;
		else if (format[*i] == '-')
			flags->minus = 1;
		else if (format[*i] == '.' && ++(*i) && ++flags->dot)
		{
			flags->precision = ft_get_width_prec(format, i);
			continue ;
		}
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == ' ')
			flags->space = 1;
		else if (format[*i] == '+')
			flags->plus = 1;
		*i += 1;
	}
}

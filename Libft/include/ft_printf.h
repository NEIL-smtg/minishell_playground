/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:42:11 by suchua            #+#    #+#             */
/*   Updated: 2023/04/01 05:09:54 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_flag
{
	int		zero;
	int		minus;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
}	t_flag;

# define PRINT 1
# define SPACE_NOW 1
# define SPACE_LATER 2
# define LOWER 1
# define UPPER 2

//flags
void	ft_set_flags(t_flag	*flags);
void	ft_get_flags(t_flag *flags, const char *format, int *i);

//ch
int		ft_print_ch(char c, t_flag *flags);

//str
int		ft_print_str(char *str, t_flag *flags);
void	ft_print_rep(int width, char c);

//%d
int		ft_nb_central(int nbr, t_flag *flags);
int		ft_print_nb(t_flag *flags, char *nbrstr);
int		ft_print_plus_sp(t_flag *flags, char *nbrstr);

//%u
int		ft_usnb_central(unsigned int nbr, t_flag *flags);
void	ft_print_usnb(unsigned int nbr);
int		ft_before_print_usnb(t_flag *flags, unsigned int nbr, int nbrlen);
int		ft_print_us_plus_sp(t_flag *flags);

//%p %xX
int		ft_print_address(void *content, t_flag *flags);
void	ft_print_hex(unsigned long address, int type);
int		ft_print_hex_central(unsigned long nb, t_flag *flags, int type);
int		ft_get_hex_nbrlen(unsigned long nb);
int		ft_before_print_p(t_flag *flags, unsigned long address, int nbrlen);
int		ft_before_print_hex(t_flag *flags, unsigned long nb, int type);
void	ft_write_prefix(int type);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:41:31 by suchua            #+#    #+#             */
/*   Updated: 2023/04/01 05:09:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FILE_D_SIZE
#  define FILE_D_SIZE 8192
# endif

//utils
int		ft_strlen_n(char *str);
void	ft_clean(char *partial);
int		ft_contain_n(char *str);

#endif
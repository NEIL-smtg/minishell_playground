/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:26:50 by suchua            #+#    #+#             */
/*   Updated: 2022/10/11 12:38:13 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) s;
	while (i < n)
		str[i++] = 0;
}

// int	main(void)
// {
// 	char	str[] = "werthytr3ergh";
// 	ft_bzero(str, 5);
// 	int i = -1;
//	while (++i < ft_strlen(str))
//		printf("%c ",str[i]);
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:16:16 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:24:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= '\0' && c <= 127);
}

// int main(void)
// {
// 	int	res1 = ft_isascii('\0' - 1);
// 	int	res2 = ft_isascii(128);
// 	int	res3 = ft_isascii(127);
// 	printf("res1 = %d\nres2 = %d\nres3 = %d\n", res1, res2, res3);
// 	return (0);
// }
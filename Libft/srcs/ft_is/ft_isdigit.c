/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:20:56 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:24:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// int main(void)
// {
// 	int	res1 = ft_isascii(5);
// 	int	res2 = ft_isascii('5');
// 	printf("res1 = %d\nres2 = %d\n, res1, res2);
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:22:27 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:24:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

// int main(void)
// {
// 	int	res1 = ft_isalnum('6');
// 	int	res2 = ft_isalnum('a');
// 	int	res3 = ft_isalnum('T');
//	int res4 = ft_isalpha('0' - 1);
//	int res5 = ft_isalpha('9' + 1);
// 	printf("res1 = %d\nres2 = %d\nres3 = %d\n
//res4 = %d\nres5 = %d\n", res1, res2, res3, res4, res5);
// 	return (0);
// }
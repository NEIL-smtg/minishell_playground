/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:01:09 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:25:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')));
}

// int main(void)
// {
// 	int	res1 = ft_isalpha('6');
// 	int	res2 = ft_isalpha('a');
// 	int	res3 = ft_isalpha('T');
//	int res4 = ft_isalpha('0' - 1);
// 	printf("res1 = %d\nres2 = %d\nres3 = %d
//res4 = %d", res1, res2, res3, res4);
// 	return (0);
// }
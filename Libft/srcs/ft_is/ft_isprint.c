/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:34:57 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:24:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c < 127 && c >= 32);
}

// int main(void)
// {
// 	int	res1 = ft_isprint('g');
// 	int	res2 = ft_isprint(127);
// 	int	res3 = ft_isprint(126);
// 	printf("res1 = %d\nres2 = %d\nres3 = %d\n", res1, res2, res3);
// 	return (0);
// }
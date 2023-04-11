/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:36:35 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:08:18 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	dosmtg(unsigned int a, char *str)
// {
// 	*str += a;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!f || !s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int main(void)
// {
// 	char	str[] = "abcdefghijkl";
// 	printf("before : %s\n", str);
// 	ft_striteri(str, dosmtg);
// 	printf("after : %s\n", str);
// 	return (0);
// }
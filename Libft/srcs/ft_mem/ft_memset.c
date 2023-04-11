/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:44:26 by suchua            #+#    #+#             */
/*   Updated: 2022/10/11 19:00:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	char			*ptr;
	unsigned char	ch;

	i = 0;
	ptr = str;
	ch = c;
	while (i < n)
	{
		ptr[i] = ch;
		i++;
	}
	return (str);
}

// #include <string.h>

// int main(void)
// {
// 	char str[] = "dfghjkl";
// 	char *g = ft_memset(str + 2, '/', 3);
// 	printf("%s",g);
// 	return (0);
// }
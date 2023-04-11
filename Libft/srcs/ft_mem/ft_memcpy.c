/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:32:36 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:49:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t	n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	if (!dest && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	while (i < n)
	{
		*d++ = *s++;
		i++;
	}
	return (dest);
}

// #include <string.h>

// int main()
// {
// 	char str[] = "stackoverflaw";
// 	memcpy(str+6, str + 4, 7);
// 	printf("%s\n",str);

// 	return (0);
// }
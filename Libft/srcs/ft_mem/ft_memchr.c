/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:22:52 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:35:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	//locate first occurence of chr
// 	char	str[] = "ertyhengfds";
// 	printf("memchr = %s\n", ft_memchr(str, 'e', 4));
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:47:52 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:21:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	while (n-- > 0)
		d[n] = s[n];
	return (dest);
}

// int main(void)
// {
// 	char ori[] = "i am going to sleep";
// 	char *src = ori + 3;
// 	src = am going to sleep;
// 	char *dst = ori + 7;
// 	dst = oing to sleep;
// 	memmove(dst, src, 6);
// 	printf("%s",ori);

// 	char *s = src + n;
// 	*s = 'i';
// 	char *d = dst + n;
// 	*d = 't';

// 	while (n >= 0)
// 		d[n] = s[n]
// 		n--;
// 	return (d);
// }
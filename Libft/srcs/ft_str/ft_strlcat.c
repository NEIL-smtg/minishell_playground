/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:20:17 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:47:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	j;
	size_t	src_len;

	if ((!dst && !dstsize) || ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	j = 0;
	while (src[j] && j < dstsize - dst_len - 1)
	{
		dst[dst_len + j] = src[j];
		j++;
	}
	dst[dst_len + j] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char	dst[] = "0123456789";
// 	char	src[] = "qwertyuiop";

// 	printf("before :\nsrc = %s\ndst = %s\n", src, dst);
// 	ft_strlcat(dst, src, 20);
// 	printf("\n\nafter :\nsrc = %s\ndst = %s\n", src, dst);
// 	printf("dst");

// 	char d[] = "0123456789";
// 	char s[] = "qwertyuiop";
// 	printf("\nbefore :\nsrc = %s\ndst = %s\n", s, d);
// 	ft_strlcat(dst, src, 15);
// 	printf("\n\nafter :\nsrc = %s\ndst = %s\n", s, d);
// 	printf("dst");
// 	return (0);
// }
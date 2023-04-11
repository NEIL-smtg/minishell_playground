/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:46:52 by suchua            #+#    #+#             */
/*   Updated: 2022/10/13 18:24:00 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && *haystack)
	{
		j = 0;
		while (haystack[j] == needle[j] && needle[j] && haystack[j])
		{
			if (j + i > len - 1)
				break ;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}

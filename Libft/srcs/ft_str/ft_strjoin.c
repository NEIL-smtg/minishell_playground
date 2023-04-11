/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:28:23 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:10:52 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	concat(char *str, char const *a)
{
	size_t	n;

	n = ft_strlen(str);
	while (*a)
		str[n++] = *(a++);
	str[n] = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *) malloc (total_size * sizeof(char));
	if (!str)
		return (NULL);
	*str = 0;
	concat(str, s1);
	concat(str, s2);
	return (str);
}

// int main(void)
// {
// 	const char s1[]= "erfghnm";
// 	const char s2[] = "sdcfgh";
// 	printf("%s\n%lu",ft_strjoin(s1, s2), ft_strlen(ft_strjoin(s1, s2)));
// 	return (0);
// }

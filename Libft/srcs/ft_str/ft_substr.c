/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:33 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:30:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	st;
	size_t	i;
	char	*tmp;

	st = (unsigned int)start;
	if (!s)
		return (NULL);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	else
		tmp = (char *) malloc ((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[st] && i < len)
		tmp[i++] = s[st++];
	tmp[i] = '\0';
	return (tmp);
}

// int main(void)
// {
// 	printf("%s\n",ft_substr("tripouille", 1, 1));
// 	return (0);
// }
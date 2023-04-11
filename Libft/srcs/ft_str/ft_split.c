/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:33:34 by suchua            #+#    #+#             */
/*   Updated: 2023/04/01 17:48:35 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**recursive_split(char const *s, char c, int depth)
{
	int		i;
	char	*str;
	char	**strs;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	str = ft_substr(s, 0, (size_t) i);
	if (!str)
		return (NULL);
	while (s[i] && s[i] == c)
		++i;
	if (s[i])
		strs = recursive_split(s + i, c, depth + 1);
	else
		strs = ft_calloc(depth + 2, sizeof(char *));
	if (!strs)
		return (NULL);
	strs[depth] = str;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	if (!s)
		return (ft_calloc(1, sizeof(char *)));
	return (recursive_split(s, c, 0));
}

// int main(void)
// {
// 	char const str[] = "      split       this for   me  !       ";
// 	char c = (char)' ';
// 	char **p = ft_split(str, c);
// 	int	i = -1;
// 	while (p[++i])
// 	{
// 		ft_printf("%s\n", p[i]);
// 		free(p[i]);
// 	}
// 	free(p);
// 	return (0);
// }
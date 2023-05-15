/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:55:11 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 18:00:35 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	get_strs_len(char **s, int size, char *sep)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	while (++i < size)
		n += len(s[i]);
	n += (size - 1) * len(sep) + 1;
	return (n);
}

static void	concat(char *tab, char *sep)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
		i++;
	j = 0;
	while (sep[j])
	{
		tab[i + j] = sep[j];
		j++;
	}
	tab[i + j] = '\0';
}

char	*ft_2dstrjoin(int size, char **strs, char *sep)
{
	char	*tab;
	int		i;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	tab = (char *)malloc(get_strs_len(strs, size, sep) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[0] = '\0';
	i = -1;
	while (++i < size)
	{
		concat(tab, strs[i]);
		if (i != size - 1)
			concat(tab, sep);
	}
	return (tab);
}

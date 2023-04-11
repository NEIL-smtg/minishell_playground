/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:13:23 by suchua            #+#    #+#             */
/*   Updated: 2023/04/06 19:48:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*duplicate;
	int		i;

	duplicate = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		duplicate[i] = src[i];
	duplicate[i] = '\0';
	return (duplicate);
}

char	**ft_2d_strdup(char **src)
{
	int		row;
	char	**new;
	int		i;

	row = 0;
	while (src[row])
		++row;
	new = malloc(sizeof(char *) * (row + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < row)
		new[i] = ft_strdup(src[i]);
	new[i] = 0;
	return (new);
}

char	**ft_2d_strndup(char **src, int n)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (n + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < n)
		new[i] = ft_strdup(src[i]);
	new[i] = 0;
	return (new);
}

void	ft_free2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

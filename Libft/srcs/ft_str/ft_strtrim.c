/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:46:01 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 18:31:02 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char me, char const *set)
{
	while (*set)
	{
		if (me == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	get_actual_len(char const *str, char const *set)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str) - 1;
	while (check_set(str[i], set) && str[i])
		i++;
	while (check_set(str[len], set) && len > i)
		len--;
	len++;
	return (len - i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	len = get_actual_len(s1, set);
	tmp = (char *) malloc (len * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (check_set(*s1, set) && s1)
		s1++;
	while (len - 1 > 0)
	{
		tmp[i++] = *s1++;
		len--;
	}
	tmp[i] = '\0';
	return (tmp);
}

// int main(void)
// {
// 	char s1[] = "\t   \n\n\n  \n\n\t    
//Hello \t  Please\n Trim me ! \t\t\t\n  \t\t\t\t  ";
// 	char s2[] = " \n\t";
// 	printf("%s\n%d",ft_strtrim(s1, s2), get_actual_len(s1, s2));
// 	return (0);
// }
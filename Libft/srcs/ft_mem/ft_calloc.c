/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:52:13 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 15:46:57 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count >= SIZE_MAX / size)
		return (NULL);
	ptr = (void *) malloc (count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// int main(void)
// {
// 	if (!ft_calloc(SIZE_MAX, SIZE_MAX))
// 		printf("ft_calloc(SIZE_MAX, SIZE_MAX) = NULL\n");

// 	char *arr;
// 	arr = ft_calloc(3, sizeof(char));
// 	int i = -1;
// 	i = -1;
// 	while (++i < 3)
// 	{
// 		if (arr[i] == '\0')
// 			printf("(null elem) ");
// 		else
// 			printf("%c ", arr[i]);
// 	}
// 	return (0);
// }
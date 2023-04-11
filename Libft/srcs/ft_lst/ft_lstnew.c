/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:11:12 by suchua            #+#    #+#             */
/*   Updated: 2022/10/06 15:39:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = malloc (sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem -> content = content;
	new_elem -> next = NULL;
	return (new_elem);
}

// int	main(void)
// {
// 	t_list	*tmp;
// 	char	content[] = "dsfg";
// 	tmp = ft_lstnew(content);
// 	printf("tmp content : %s\n",tmp -> content);
// 	if (tmp -> next == NULL)
// 		printf("%s","NULL");
// 	return (0);
// }
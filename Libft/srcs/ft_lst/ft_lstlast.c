/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:36:38 by suchua            #+#    #+#             */
/*   Updated: 2022/10/08 17:45:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

// int	main(void)
// {
// 	t_list	*l;
// 	t_list	*first;

// 	l = NULL;
// 	ft_lstadd_front(&l, ft_lstnew((void *)34));
// 	ft_lstadd_front(&l, ft_lstnew((void *)36));
// 	ft_lstadd_front(&l, ft_lstnew((void *)39));
// 	ft_lstadd_front(&l, ft_lstnew((void *)55));
// 	first = ft_lstnew((void *)7);
// 	ft_lstadd_front(&l, first);
// 	printf("%d",(int) ft_lstlast(first) -> content);
// }
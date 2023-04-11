/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:47:34 by suchua            #+#    #+#             */
/*   Updated: 2022/10/08 17:56:27 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
	else
		*lst = new;
}

// int	main(void)
// {
// 	t_list	*l = NULL;
// 	//t_list	*new;
// 	//t_list	*last;

// 	//l = ft_lstnew((void *)34);
// 	// ft_lstadd_front(&l, ft_lstnew((void*)1));

// 	// ft_lstadd_front(&l, ft_lstnew((void *)36));
// 	// ft_lstadd_front(&l, ft_lstnew((void *)39));
// 	// ft_lstadd_front(&l, ft_lstnew((void *)55));

// 	ft_lstadd_back(&l, ft_lstnew((void *)7));
// 	ft_lstadd_back(&l, ft_lstnew((void *)27));

// 	printf("%d", (int) l -> content);
// }
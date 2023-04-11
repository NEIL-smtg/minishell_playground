/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:39:48 by suchua            #+#    #+#             */
/*   Updated: 2022/10/11 12:44:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new -> next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*l = NULL;
//t_list	*new;
//t_list	*last;

//l = ft_lstnew((void *)34);
// ft_lstadd_front(&l, ft_lstnew((void*)1));

// ft_lstadd_front(&l, ft_lstnew((void *)36));
// ft_lstadd_front(&l, ft_lstnew((void *)39));
// ft_lstadd_front(&l, ft_lstnew((void *)55));

// 	ft_lstadd_front(&l, ft_lstnew((void *)7));
// 	ft_lstadd_front(&l, ft_lstnew((void *)27));

// 	printf("%d", (int) l -> content);
// }
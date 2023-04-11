/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:32:16 by suchua            #+#    #+#             */
/*   Updated: 2022/10/11 16:17:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_lstnew(f(lst -> content));
	if (!new_lst)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	lst = lst -> next;
	while (lst)
	{
		elem = ft_lstnew(f(lst -> content));
		if (!elem)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_lst, del);
			break ;
		}
		lst = lst -> next;
		ft_lstadd_back(&new_lst, elem);
	}
	return (new_lst);
}

// void * addOne(void * p)
// {
// 	void * r = malloc(sizeof(int));
// 	*(int*)r = *(int*)p + 1;
// 	return (r);
// }

// int main(void)
// {
// 	int tab[] = {0, 1, 2, 3};
// 	t_list * l =  ft_lstnew(tab);
// 	for (int i = 1; i < 4; ++i)
// 		ft_lstadd_back(&l, ft_lstnew(tab + i));
// 	t_list * m = ft_lstmap(l, addOne, free);
// 	t_list * tmp = l;
// 	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
// 	{
// 		printf("%d ",*(int*)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	tmp = m;
// 	/* 5 6 7 8 */ for (int i = 0; i < 4; ++i)
// 	{
// 		printf("%d ",*(int*)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:44:34 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:01:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirlst_addback(t_redirlst **rlst, char *filename, int fd)
{
	t_redirlst	*new;
	t_redirlst	*tmp;	

	if (fd == -1)
	{
		perror("open");
		return ;
	}
	new = ft_calloc(1, sizeof(t_redirlst));
	new->next = NULL;
	new->filename = ft_strdup(filename);
	new->fd = fd;
	if (!rlst || !*rlst)
		*rlst = new;
	else
	{
		tmp = *rlst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

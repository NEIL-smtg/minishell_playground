/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:52:06 by suchua            #+#    #+#             */
/*   Updated: 2022/10/12 16:08:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write (fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}

// int main(void)
// {
// 	char s[] = "fsdfsdfs";
// 	ft_putendl_fd(s, 4);
// 	return (0);
// }

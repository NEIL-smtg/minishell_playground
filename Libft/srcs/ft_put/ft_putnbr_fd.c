/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:55:34 by suchua            #+#    #+#             */
/*   Updated: 2022/10/06 17:17:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	ch;

	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n / 10 > 0)
	{
		ft_putnbr_fd(n / 10, fd);
		ch = n % 10 + '0';
		write(fd, &ch, 1);
	}
	else
	{
		ch = n % 10 + '0';
		write (fd, &ch, 1);
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648, 0);
// 	return (0);
// }

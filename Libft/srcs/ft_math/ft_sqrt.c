/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:14:54 by suchua            #+#    #+#             */
/*   Updated: 2023/04/03 00:15:35 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double nb)
{
	double	root;
	int		i;

	root = 1;
	i = 0;
	while (1)
	{
		++i;
		root = (nb / root + root) / 2;
		if (i == nb + 1)
			break ;
	}
	return (root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:15:16 by suchua            #+#    #+#             */
/*   Updated: 2023/03/24 02:33:21 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_pipenum(char *str)
{
	int		npipe;
	int		i;
	char	type;

	npipe = 0;
	i = 0;
	type = str[0];
	while (str[i] && (str[i] == '|' || str[i] == '&'))
	{
		++npipe;
		if (str[i] != type || npipe > 2)
		{
			ft_putstr_fd("minishell: parse error near \'", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("\'", 2);
			return (0);
		}
		++i;
	}
	return (1);
}

int	dangling_pipe(char *str)
{
	int	i;

	i = 0;
	add_history(str);
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '&') && !valid_pipenum(&str[i]))
			return (0);
		++i;
	}
	i = ft_strlen(str) - 1;
	if (str[i] == '|' || str[i] == '&')
	{
		ft_putstr_fd("minishell: parse error near \'", 2);
		ft_putchar_fd(str[i], 2);
		ft_putendl_fd("\'", 2);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:59:48 by suchua            #+#    #+#             */
/*   Updated: 2023/04/26 20:12:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dangling_redir2(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '>')
			++i;
		if (!str[i])
			break ;
		if (str[i++] == '>')
			while (str[i] && ft_isspace(str[i]))
				++i;
		if (str[i] == '<')
		{
			ft_putendl_fd("minishell: parse error near >", 2);
			return (1);
		}
	}
	return (0);
}

int	dangling_redir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '<')
			++i;
		if (!str[i])
			break ;
		if (str[i++] == '<')
			while (str[i] && ft_isspace(str[i]))
				++i;
		if (str[i] == '>')
		{
			ft_putendl_fd("minishell: parse error near <", 2);
			return (1);
		}
	}
	return (dangling_redir2(str));
}

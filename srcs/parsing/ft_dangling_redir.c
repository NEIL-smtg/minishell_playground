/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:59:48 by suchua            #+#    #+#             */
/*   Updated: 2023/05/03 16:20:49 by suchua           ###   ########.fr       */
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

static int	valid_number_redir(char *str)
{
	int	i;

	i = 0;
	while (*str && i <= 2)
	{
		i = 0;
		while (str[i] && str[i] == '<')
			++i;
		if (i > 2)
			break ;
		i = 0;
		while (str[i] && str[i] == '>')
			++i;
		if (i > 2)
			break ;
		str += i + 1;
	}
	if (i > 2 && *(str + i - 1) == '<')
		ft_putendl_fd("minishell: parse error near <", 2);
	if (i > 2 && *(str + i - 1) == '>')
		ft_putendl_fd("minishell: parse error near >", 2);
	return (i > 2);
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
	return (dangling_redir2(str) || valid_number_redir(str));
}

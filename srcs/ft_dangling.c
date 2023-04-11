/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:22:02 by suchua            #+#    #+#             */
/*   Updated: 2023/03/24 01:15:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dangling_squote(char *str)
{
	int	squote;
	int	i;

	squote = 0;
	i = 0;
	while (ft_strchr(&str[i], 39))
	{
		squote = !squote;
		while (str[i] && str[i] != 39)
			++i;
		if (!str[i])
			break ;
		++i;
	}
	return (squote);
}

int	dangling_dquote(char *str)
{
	int	dquote;
	int	i;

	dquote = 0;
	i = 0;
	while (ft_strchr(&str[i], 34))
	{
		dquote = !dquote;
		while (str[i] && str[i] != 34)
			++i;
		if (!str[i])
			break ;
		++i;
	}
	return (dquote);
}

int	dangling_bracket(char *str)
{
	int	len;
	int	count;
	int	i;

	i = 0;
	len = ft_strlen(str);
	count = 0;
	while (i < len)
	{
		if (str[i] == '(')
			++count;
		else if (str[i] == ')')
		{
			--count;
			if (count < 0)
				return (0);
		}
		++i;
	}
	return (count == 0);
}

int	ft_dangling(char *str, int print)
{
	if (dangling_dquote(str) || dangling_squote(str) || !dangling_bracket(str))
	{
		if (print)
		{
			add_history(str);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		}
		return (0);
	}
	return (1);
}
